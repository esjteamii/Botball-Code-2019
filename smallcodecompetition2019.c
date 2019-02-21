//Created on Fri September 14 2018
#include <kipr/botball.h>

//Port number variables for the motors, servos, and sensors
int leftmotor = 0;
int rightmotor = 1;
int armservo = 0;
int clawservo = 1;
int patservo = 2;
int button = 0;
int light = 0;
int ltophat = 1;
int rtophat = 2;
int etsensor = 3;

//Servo position variables
int armdown = 1850;
int armup = 500;
int armback = 150;
int clawopen = 2000;
int clawclosed = 650;
int patup = 1400;
int patdown = 100;

int i;//This is used in 'for' loops

//Function Declarations
void msmove(int speed, int msecs);
void msturn(int speed, int msecs);
void raisearm();
void lowerarm();
void pusharm();
void collect();
void openclaw();
void closeclaw();
void patunit();
void slowservo(int port, int pos);
void linefollow();
void pause(int msecs);

int rmotoroffset = 22;

//Cm to tick conversion: 1 cm = 80 ticks

int main()
{   
    enable_servos();
    //wait_for_light(light);
    //shut_down_in(115);

    //Start of actions--------------------------------
    //Moves until fire station black tape
    msmove(1000, 2000);
    while(analog(1) < 1000)
    {
        mav(leftmotor, 1000);
        mav(rightmotor, 970);
    }
    pause(250);
    
    //Turns and aligns with pipe
    msmove(-1000, 150);
    msturn(1500, 600);
    msmove(-1000, 1800);
    
    //Goes until black line
    msturn(500, 200);
    raisearm();
    while(analog(ltophat) < 1500)
    {
        mav(leftmotor, 1000);
        mav(rightmotor, 1000);
    }
    
    //Turn and line up using both tophats
    msturn(-1000, 600);
    while(analog(rtophat) < 1500)
    {
        mav(leftmotor, 1000);
        mav(rightmotor, 1000);
    }
    msmove(1000, 1100);
    while(analog(ltophat) < 1500 || analog(rtophat) < 1500)
    {
        if(analog(ltophat) < 1500)
        {
            mav(leftmotor, 500);
            mav(rightmotor, -250);
        }
        else
        {
            mav(leftmotor, -250);
            mav(rightmotor, 500);
        }
    }
    
    //Grabs the first group of puffballs
    msturn(500, 1200);
    while(analog(ltophat) < 1600)
    {
        mav(leftmotor, -250);
        mav(rightmotor, 250);
    }
    msturn(750, 600);
    msmove(500, 300);
    collect();
    
    //Moves toward and grabs second groups of puffballs
    msturn(-500, 500);
    msmove(750, 750);
    msturn(1000, 500);
    set_servo_position(armservo, 1400);
    msleep(250);
    while(analog(etsensor) > 2800)
    {
        mav(leftmotor, 500);
        mav(rightmotor, 500);
    }
    
    for(i = 0; i < 1000; i++)
    {
        if(analog(etsensor) < 2800)
        {
            mav(leftmotor, 500);
            mav(rightmotor, 350);
        }
        else if(analog(etsensor) > 2800)
        {
            mav(leftmotor, 350);
            mav(rightmotor, 500);
        }
    }
    collect();
    /*
    //Follows pipe to third group and grabs it
    set_servo_position(armservo, 1400);
    msleep(250);
    for(i = 0; i < 2000; i++)
    {
        if(analog(etsensor) < 2800)
        {
            mav(leftmotor, 500);
            mav(rightmotor, 350);
        }
        else if(analog(etsensor) > 2800)
        {
            mav(leftmotor, 350);
            mav(rightmotor, 500);
        }
    }
    msturn(-100, 100);
    openclaw();
    lowerarm();
    msmove(500, 500);
    closeclaw();
    collect();
    patunit();
    
    //Follows pipe to fourth group and grabs it
    set_servo_position(armservo, 1400);
    msleep(250);
    for(i = 0; i < 750; i++)
    {
        if(analog(etsensor) < 2800)
        {
            mav(leftmotor, 500);
            mav(rightmotor, 200);
        }
        else if(analog(etsensor) > 2800)
        {
            mav(leftmotor, 200);
            mav(rightmotor, 500);
        }
    }
    msmove(1000, 900);
    for(i = 0; i < 400; i++)
    {
        if(analog(etsensor) < 2800)
        {
            mav(leftmotor, 750);
            mav(rightmotor, 500);
        }
        else if(analog(etsensor) > 2800)
        {
            mav(leftmotor, 500);
            mav(rightmotor, 750);
        }
    }
    openclaw();
    msturn(-250, 500);
    lowerarm();
    msmove(500, 500);
    msturn(250, 500);
    closeclaw();
    collect();
    patunit();
    
    //Follows pipe to fifth group
    set_servo_position(armservo, 1400);
    for(i = 0; i < 2000; i++)
    {
        if(analog(etsensor) < 2600)
        {
            mav(leftmotor, 500);
            mav(rightmotor, 450);
        }
        else if(analog(etsensor) > 2800)
        {
            mav(leftmotor, 450);
            mav(rightmotor, 500);
        }
    }
    pause(1000);
    msmove(500, 600);
    pause(500);
    msturn(-250, 300);
    openclaw();
    lowerarm();
    msturn(250, 200);
    closeclaw();
    collect();
    patunit();
    
    //Place unit in utility zone
    raisearm();
    msturn(500, 250);
    msmove(1000, 4000);
    msturn(500, 1800);
    lowerarm();
    for(i = 0; i < 1200; i++)
    {
        if(analog(etsensor) < 2700)
        {
            mav(leftmotor, 1000);
            mav(rightmotor, 1000);
        }
        else if(analog(etsensor) > 2700)
        {
            mav(leftmotor, 1000);
            mav(rightmotor, 800);
        }
    }
    raisearm();
    while(analog(ltophat) < 1500)
    {
        mav(leftmotor, 1000);
        mav(rightmotor, 1000);
    }
    msmove(1000, 2500);
    msmove(-1000, 2000);
    
    //*/
    disable_servos();
    return 0;
}

void msmove(speed, msecs)
{
    mav(leftmotor, speed);
    mav(rightmotor, speed - rmotoroffset);
    msleep(msecs);
    pause(10);
}

void msturn(speed, msecs)
{
    mav(leftmotor, speed);
    mav(rightmotor, -speed);
    msleep(msecs);
    pause(10);
}

void raisearm()
{
    set_servo_position(armservo, armup);
    msleep(100);
}

void lowerarm()
{
    set_servo_position(armservo, armdown);
    msleep(100);
}

void pusharm()
{
    set_servo_position(armservo, 1600);
    msleep(100);
}

void collect()
{
    pause(10);
    set_servo_position(armservo, 1600);
    msleep(100);
    openclaw();
    msleep(250);
    lowerarm();
    msmove(500, 500);
    msturn(300, 300);
    closeclaw();
    msturn(-300, 300);
    set_servo_position(armservo, armback);
    msleep(500);
    slowservo(clawservo, 1500);
    msleep(100);
    set_servo_position(armservo, 250);
    msleep(100);
    set_servo_position(armservo, armback);
    msleep(100);
    set_servo_position(clawservo, clawclosed);
    msleep(100);
    set_servo_position(armservo, armup);
    msleep(100);
}

void openclaw()
{
    set_servo_position(clawservo, clawopen);
    msleep(100);
}
//This claw close function is built to close onto puffballs, not larger objects
void closeclaw()
{
    slowservo(clawservo, clawclosed);
    msleep(100);
}

void patunit()
{
    set_servo_position(armservo, 700);
    msleep(100);
    set_servo_position(patservo, patdown);
    msleep(250);
    set_servo_position(patservo, patup);
    msleep(250);
}

void slowservo(port, pos)
{
    pause(100);
    if(get_servo_position(port) < pos)
    {
        for(i = get_servo_position(port); i < pos; i = i + 10)
        {
            set_servo_position(port, i);
            msleep(10);
        }
    }
    else if(get_servo_position(port) > pos)
    {
        for(i = get_servo_position(port); i > pos; i = i - 10)
        {
            set_servo_position(port, i);
            msleep(10);
        }
    }
}

//Less than 1500 means white, greater means black (or darker color)
void linefollow()
{
    while(digital(0) == 0)
    {
        if(analog(1) < 1500 && analog(2) < 1500)
        {
            mav(leftmotor, 1000);
            mav(rightmotor, 1000);
        }
        else if(analog(1) < 1500 && analog(2) > 1500)
        {
            mav(leftmotor, 750);
            mav(rightmotor, -250);
        }
        else if(analog(1) > 1500 && analog(2) < 1500)
        {
            mav(leftmotor, -250);
            mav(rightmotor, 750);
        }
        else
        {
            mav(leftmotor, 500);
            mav(rightmotor, 500);
        }
    }
}

void pause(msecs)
{
    freeze(leftmotor);
    freeze(rightmotor);
    msleep(msecs);
}
