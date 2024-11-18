#include <ros.h>
#include <ArduinoHardware.h>

#include <rospy_tutorials/Floats.h>
#include <Floats_array.h>
#include <Servo.h> 

ros::NodeHandle nh;

int cur_pos[6]={0,0,0,0,0,0};

Servo servo1,servo2,servo3,servo4,servo5,servo6;

float readservo1=0,readservo2=0,readservo3=0,readservo4=0,readservo5=0,readservo6=0;

void rotate_servo(int servo,int new_pos,int cur_pos,int dir)
{
  int pos = 0;
  
  if (servo==0)
  {
    if (new_pos<5)
      new_pos=5;
    if (dir == 1)
    {
      for(pos=cur_pos;pos<= new_pos;pos += 1)
      {
        servo1.write(pos);
        delay(10);
      }      
    }
    else if(dir == -1)
    {
      for(pos=cur_pos;pos>= new_pos;pos -= 1)
      {
        servo1.write(pos);
        delay(10);
      }      
    }
  }
  if (servo==1)
  {
    if (new_pos<12)
      new_pos=12;
    else if(new_pos>161)
    {
      //nh.loginfo("Limiting Servo2 to 155");
      new_pos=155;
    }
    
    if (dir == 1)
    {
      for(pos=cur_pos;pos<= new_pos;pos += 1)
      {
        servo2.write(pos);
        delay(10);
      }      
    }
    else if(dir == -1)
    {
      for(pos=cur_pos;pos>= new_pos;pos -= 1)
      {
        servo2.write(pos);
        delay(10);
      }      
    }
  }
  if (servo==2)
  {
    if (new_pos<6)
      new_pos=6;
    if (dir == 1)
    {
      for(pos=cur_pos;pos<= new_pos;pos += 1)
      {
        servo3.write(pos);
        delay(10);
      }      
    }
    else if(dir == -1)
    {
      for(pos=cur_pos;pos>= new_pos;pos -= 1)
      {
        servo3.write(pos);
        delay(10);
      }      
    }
  }
  if (servo==3)
  {
    if (new_pos<5)
      new_pos=5;
    if (dir == 1)
    {
      for(pos=cur_pos;pos<= new_pos;pos += 1)
      {
        servo1.write(pos);
        delay(10);
      }      
    }
    else if(dir == -1)
    {
      for(pos=cur_pos;pos>= new_pos;pos -= 1)
      {
        servo1.write(pos);
        delay(10);
      }      
    }
  }
  if (servo==4)
  {
    if (new_pos<5)
      new_pos=5;
    if (dir == 1)
    {
      for(pos=cur_pos;pos<= new_pos;pos += 1)
      {
        servo1.write(pos);
        delay(10);
      }      
    }
    else if(dir == -1)
    {
      for(pos=cur_pos;pos>= new_pos;pos -= 1)
      {
        servo1.write(pos);
        delay(10);
      }      
    }
  }
  if (servo==5)
  {
    if (new_pos<6)
      new_pos=6;
    if (dir == 1)
    {
      for(pos=cur_pos;pos<= new_pos;pos += 1)
      {
        servo3.write(pos);
        delay(10);
      }      
    }
    else if(dir == -1)
    {
      for(pos=cur_pos;pos>= new_pos;pos -= 1)
      {
        servo3.write(pos);
        delay(10);
      }      
    }
  }
}


void servo_cb(const rospy_tutorials::Floats& cmd_msg)
{
  //nh.loginfo("Command Received");
  
  int new_pos[6]={cmd_msg.data[0],cmd_msg.data[1],cmd_msg.data[2],cmd_msg.data[3],cmd_msg.data[4],cmd_msg.data[5]};
  int i=0;
  
  for(i=0;i<6;i++)
  {
    if (new_pos[i]>cur_pos[i])
    {
      rotate_servo(i,new_pos[i],cur_pos[i],1);
      cur_pos[i]=new_pos[i];
        
    }
    else if(new_pos[i]<cur_pos[i])
    {
      rotate_servo(i,new_pos[i],cur_pos[i],-1);
      cur_pos[i]=new_pos[i];
    }
    
  }
  
}

void callback(const robotic_armv5::Floats_array::Request& req, robotic_armv5::Floats_array::Response& res)
{
  // Since no potentiometer is used, we are not reading any sensor data.
  // So, we return fixed values or other data as required.
  
  res.res_length = 6;
  res.res[0] = cur_pos[0];  // Return current position of servo 1
  res.res[1] = cur_pos[1];  
  res.res[2] = cur_pos[2];
  res.res[3] = cur_pos[3]; 
  res.res[4] = cur_pos[4];  
  res.res[5] = cur_pos[5];  


  return;
}




ros::Subscriber<rospy_tutorials::Floats> sub("/joints_to_aurdino", servo_cb);
ros::ServiceServer<robotic_armv5::Floats_array::Request, robotic_armv5::Floats_array::Response> server("/read_joint_state",&callback);


void setup(){

  nh.initNode();
  nh.subscribe(sub);
  nh.advertiseService(server);
  
  servo1.attach(6);
  servo2.attach(9);
  servo3.attach(11);
  servo4.attach(3); 
  servo5.attach(5);
  servo6.attach(10);
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
  servo5.write(0);
  servo6.write(0);
  
}

void loop(){

  nh.spinOnce();
  delay(20);
}
