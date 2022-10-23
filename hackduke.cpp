#define NOTIF_FREQ 0.5
#define SAMPLE_FREQ 10
#define SAMPLING_WINDOW 100
#define MIN_BOTTLE_WEIGHT 20
#define MOVING_AVERAGE_WINDOW 50

const int led_pin = D0; 
const int sensor_pin = A5;

//Variables
String msg = "Drink your water!!!!!";
int current_time_millis;
int start_time_millis;
double last_water_vol;
double current_water_vol;
int sensor_out;
double samples[MOVING_AVERAGE_WINDOW];
bool init_sample;
bool waiting_for_place;
double max_sample;
double average_sample;
double moving_average;
double total_amt_to_drink = 480;
double total_amt_drank;
double amt_drank_in_period;
double amt_to_drink_in_period = 60;
bool led_on;
bool skip;

//Function Prototypes
void send_data();
double calc_water_vol();
void add_sample(double *, double);
double calc_moving_average(double * );
void flash_LEDS(bool);

void setup() {
    pinMode(sensor_pin, INPUT);
    pinMode(led_pin, OUTPUT);
    current_time_millis = millis();
    start_time_millis = millis();
    init_sample = false;
    waiting_for_place = false;
    max_sample = 0;
    average_sample = -1;
    led_on = false;
    total_amt_to_drink = 1000;
    skip = false;
}

void loop(){
    //If we shouldnt send a notification
    if(current_time_millis-start_time_millis <= NOTIF_FREQ * 60 * 1000){
        //Sampling Code
        //Serial.println(calc_water_vol(sensor_out));
        if (calc_water_vol() < 20){
            Serial.println("bottle removed");
            waiting_for_place = true;
            led_on = false;
        }
        else if (waiting_for_place == true){
            if(calc_water_vol() > MIN_BOTTLE_WEIGHT){
                init_sample = true;
                Serial.println("bottle replaced");
            }
        }
        if (init_sample){
            delay(1000);
            Serial.println("taking sample");
            average_sample = 0;
            for(int i = 0; i<SAMPLING_WINDOW; i++){
                average_sample += calc_water_vol();
            }
            average_sample = average_sample/SAMPLING_WINDOW;
            if(average_sample > max_sample){
                max_sample = average_sample;
            }
            init_sample = false;
            waiting_for_place = false;
        }
        
    }
    //Send a notification Code
    else{
        skip = false;
        while(calc_water_vol() < 20){
            skip = true;
            Serial.println("Waiting for bottle");   
        }
        Serial.println(skip);
        if(!skip){
            Serial.println("In else");
            
            Serial.println(max_sample);
            Serial.println(average_sample);
            if ((max_sample - average_sample) < amt_to_drink_in_period) {
                Serial.println("Sending data");
                send_data();
                led_on = true;
            }else{
                led_on = false;
            }
            total_amt_drank += amt_drank_in_period;
            amt_drank_in_period = 0;
            max_sample = average_sample;
        }
        start_time_millis = millis();
    }
    
    current_time_millis = millis();
    
    flash_LEDS(led_on);
    
}

void add_sample(double *samples, double sample){
    for(int i=0; i<MOVING_AVERAGE_WINDOW-1; i++){
        samples[i] = samples[i+1];
    }
    samples[MOVING_AVERAGE_WINDOW-1] = sample;
}

double calc_moving_average(double *samples){

    int avg = 0;
    for(int i=0; i<MOVING_AVERAGE_WINDOW; i++){
        avg += samples[i];
    }
    return avg/MOVING_AVERAGE_WINDOW;
}

double calc_water_vol(){
    return analogRead(A5);
}

void send_data(){
    Particle.publish("Noti", msg, 60, PRIVATE);
}

void flash_LEDS(bool led_on){
    if(led_on){
        for(int i=0; i<255; i++){
        analogWrite(led_pin, i);
        delay(5);
        }
        delay(100);
        for(int i=255; i>=0; i--){
            analogWrite(led_pin, i);
            delay(5);
        }
        delay(100);
        
    }
}


