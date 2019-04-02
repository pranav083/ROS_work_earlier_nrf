
/*###############################################################################################
 #################################################################################################
 -----------------------constant function of the start here --------------------------------------*/

#define enright  11              //enabling pwm pin on right pin
#define righta   4               //enabling right motor on/off  
#define rightb   12              //enabling right motor on/off
#define enleft   3               //enabling pwm pin on left pin
#define lefta    7               //enabling left motor on/off
#define leftb    8               //enabling left motor on/off
#define max_left 500             //defining the max value encounter by the left sensor
#define min_left 20              //defining the min value encounter by the left sensor
#define max_center 500           //defining the max value encounter by the center sensor
#define min_center 20            //defining the min value encounter by the center sensor
#define max_right 450            //defining the max value encounter by the right sensor
#define min_right 20             //defining the min value encounter by the right sensor140 154 
#define SLAVE_ADDRESS 0x08
/*-----------------------     end here                     --------------------------------------*/

/*-----( Import needed libraries )-----*/

#include<ros.h>//calling the ros header file from library
#include<geometry_msgs/Twist.h> //for suscribing the com_vel fuction

//initializing the ros node handler function
ros::NodeHandle nh;

/*-----( Declare Variables )-----*/
int dir =0,test=4;
float lin=0.0,ang=0.0,l=0.0,a=0.0;
unsigned long datarec;  // Data that will be received from the transmitter
int left1=4,left2=5,right1=6,right2=7;


//function for direction
int command(const geometry_msgs::Twist& cmd)
{
 l=cmd.linear.x;
 a=cmd.angular.z;
 }

 
void dirc(float,float)
{ 
  //move in forward direction  
  if(lin>0.0 && ang==0.0)
    {
      dir=1;
    }
    //move in backward direction
    
  else if(lin<0.0 && ang==0.0)
    {
      dir=2;
    }
    //move in left side
    
  else if(lin==0.0 && ang>0.0)
    {
      dir=3;  
    }//move in right side
    
  else if(lin==0.0 && ang<0.0)
    {
      dir=4;
    }
    //stop the bot
    
  else
    {
      dir=0;  
    }
  
    return dir;
}

//calling the suscriber of cmd_vel
ros::Subscriber<geometry_msgs::Twist> comm("cmd_vel", command );



/*--------declare any function--------*/
//function to be called for rx execution command
void exe(int)
{
  switch(datarec)
  {
   case 0: stp();       
          break;
  case 1: fwd();
          break;
  case 2: bck();
          break;
  case 3: sf_rgt();      
          break;
  case 4: sf_lft();        
          break;
  default :Serial.print("invalid");        
  }
}


/*###############################################################################################
 #################################################################################################
 ------------------      function for speed calling          ---------------------*/

//forward function both motor on

void fwd()
{
  analogWrite(enleft,  100);   //pwm value for the left motor 
  digitalWrite(lefta,  LOW );    //making left pin of motor low
  digitalWrite(leftb,  HIGH);    //making left pin of motor high
  digitalWrite(righta, LOW );    //making right pin of motor low
  digitalWrite(rightb, HIGH);    //making right pin of motor high
  analogWrite(enright, 98);   //pwm value for the left motor 
}

// left motor on
void sf_lft()
{
  analogWrite(enleft,  72);    //pwm value for the left motor 
  digitalWrite(lefta,  LOW);  //making left pin of motor low
  digitalWrite(leftb,  HIGH); //making left pin of motor high  
  digitalWrite(righta, LOW);  //making right pin of motor low
  digitalWrite(rightb, HIGH); //making right pin of motor high
  analogWrite(enright, 0);    //pwm value for the left motor 
}

//right motor on 
void sf_rgt()
{
  analogWrite(enleft,  0);    //pwm value for the left motor 
  digitalWrite(lefta,  LOW);  //making left pin of motor low
  digitalWrite(leftb,  HIGH); //making left pin of motor high
  digitalWrite(righta, LOW);  //making right pin of motor low
  digitalWrite(rightb, HIGH); //making right pin of motor high
  analogWrite(enright, 67);   //pwm value for the left motor 
}

// left motor o
void hr_lft()
{
  analogWrite(enleft,  65);   //pwm value for the left motor 95
  digitalWrite(lefta,  LOW);  //making left pin of motor low
  digitalWrite(leftb,  HIGH); //making left pin of motor high  
  digitalWrite(righta, HIGH); //making right pin of motor high
  digitalWrite(rightb, LOW);  //making right pin of motor low
  analogWrite(enright, 60);   //pwm value for the left motor 87
}
//right motor on 
void hr_rgt()
{
  analogWrite(enleft,  65);    //pwm value for the left motor 85
  digitalWrite(lefta,  HIGH);  //making left pin of motor high
  digitalWrite(leftb,  LOW);   //making left pin of motor low
  digitalWrite(righta, LOW);   //making right pin of motor low
  digitalWrite(rightb, HIGH);  //making right pin of motor high
  analogWrite(enright, 60);    //pwm value for the left motor 77

}
//backward movement
void bck()
{
  analogWrite(enleft,  50 );    //pwm value for the left motor  56 
  digitalWrite(lefta,  HIGH);   //making left pin of motor high
  digitalWrite(leftb,  LOW);    //making left pin of motor low
  digitalWrite(righta, HIGH);   //making right pin of motor high
  digitalWrite(rightb, LOW);    //making right pin of motor low
  analogWrite(enright, 45);     //pwm value for the left motor 51
}
//taking left turn in backward
void bck_lft()
{
  analogWrite(enleft,  50);     //pwm value for the left motor 
  digitalWrite(lefta,  HIGH);   //making left pin of motor high
  digitalWrite(leftb,  LOW);    //making left pin of motor low  
  digitalWrite(righta, LOW);   //making right pin of motor high
  digitalWrite(rightb, HIGH);    //making right pin of motor low
  analogWrite(enright, 0);      //pwm value for the left motor 
}
////taking right turn in backward 
void bck_rgt()
{
  analogWrite(enleft,  0);     //pwm value for the left motor 
  digitalWrite(lefta,  LOW);  //making left pin of motor high
  digitalWrite(leftb,  HIGH);   //making left pin of motor low
  digitalWrite(righta, HIGH);  //making right pin of motor high
  digitalWrite(rightb, LOW);   //making right pin of motor low
  analogWrite(enright, 45);   //pwm value for the left motor 
}
//both motor off position
void stp()
{
  digitalWrite(righta, LOW);  //making left pin of motor low
  digitalWrite(rightb, LOW);  //making left pin of motor low
  digitalWrite(lefta , LOW);  //making right pin of motor low
  digitalWrite(leftb , LOW);  //making right pin of motor low
}  
/*-------------------- speed calling function of the end here --------------------------------------*/


// setup file
void setup()
{
  Serial.begin(57600);
  nh.initNode();//initializing the ROS node 
  nh.subscribe(comm);//subscribing the comm function of ros node
  //initializing motor driver pins
  pinMode(enright, OUTPUT);                      //making the right pwm pin as enable 
  pinMode(righta, OUTPUT);                       //making the right pin as output 
  pinMode(rightb, OUTPUT);                       //making the right pin as output 
  pinMode(lefta, OUTPUT);                        //making the left  pin as output 
  pinMode(leftb, OUTPUT);                        //making the left  pin as output 
  pinMode(enleft, OUTPUT);                       //making the left pwm pin as enable 

}
//loop
void loop()
{
  nh.spinOnce();//continiously check for any update in msg
  dirc(l,a);
  exe(datarec);
}
