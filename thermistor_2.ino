#include <math.h>                    // needed for log() ... which is really ln
const int TEMP = 0;                  // pin setting to get analog temp --> ADC [0 1023]
const double beta    = 4038.0;       // from data sheet of thermistor
double  val = 0.0;


// mapping values
double V_low =  0.0;
double V_high = 5.0;                 // volts set by voltage regulator
double digiREAD_low = 0;
double digiREAD_high = 1023;         // top value for digital reading of pin A0

// voltage splitter values
double Vin = V_high;                 // used to clarify variables (5.0)
double R1 = 10730;                    // ohms (measured on the board)

// Resistor transfer functionn calcs (derived from data sheet and S-H model
// https://www.jameco.com/Jameco/Products/ProdDS/207037.pdf
// https://www.thinksrs.com/downloads/programs/therm%20calc/ntccalibrator/ntccalculator.html
double A = 1.190589571e-3;
double B = 2.272672990e-4;
double C = 0.8987097763e-7;

const double dff = 0.0;             // darrell's fudge factor (if needed)




void setup() {
  // put your setup code here, to run once:

  pinMode(TEMP, INPUT);  // set pin AO as an temperature input pin
  Serial.begin(9600);    // open up comm with the board
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(TEMP);

  //double r_infinity =

  //map voltage readout (0-5) based on digital scale from the ADC (0-1023);
  double Vout = V_low + (V_high - V_low) * (val - digiREAD_low) / (digiREAD_high - digiREAD_low);

  // use voltage divider circuit to get R2:   Vout = (R1/ (R1 + R2)) * Vin
  // solve R2  (the thermistor resistance)

  double R2 = R1 * (Vout / (Vin - Vout));

  // solve the resistor transfer functio solve A, B, C (above)
  // https://sanjit.wtf/Calibrator/webCalibrator.html (yet another place to get A, B, C)
  double rhs = A + B * log(R2) + C * pow(log(R2), 3);
  double temp_K = (1.0 / rhs) + dff;    // temperature solved in Kelvin

  double temp_C  = temp_K - 273.15;    // converted to Celcius
  double temp_F = (9.0 / 5.0) * temp_C + 32.0;  // converted to Fahrenheit

  // do some output
  Serial.print("Temperature in F:" );
  Serial.print(temp_F);
  Serial.println();
  delay(500);

}
