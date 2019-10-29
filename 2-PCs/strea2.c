#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <errno.h>

#define TRIG 5   //GPIO 24
#define ECHO 6   //GPIO 25

double distance1 = 0.0;
int stexec = 0;

void setup() {
       wiringPiSetup();
       pinMode(TRIG, OUTPUT);
       pinMode(ECHO, INPUT);

}
int getCM() {
        //Manda pulso trig
        digitalWrite(TRIG, HIGH);
        delay(0.01);      //delayMicroseconds(20);usleep (20)
        digitalWrite(TRIG, LOW);


        while(digitalRead(ECHO) == 0); //Espera echo ficar em nível alto
        double startTime = micros(); 	//marcação de tempo
        while(digitalRead(ECHO) == 1); //espera echo acabar
        double endTime = micros(); //tempo do fim do pulso - tempo inicial
        double travelTime = endTime - startTime;

        //Conversão em cm
        distance1 = (travelTime*(17000))*10e-6; //

        //printf("Distance: %.5lf us\n", travelTime);
        printf("Distance: %.5lf cm\n", distance1);
        return 1;
}
void stream(){
	stexec=1;
	char buffer_ent[100];
	char buffer_sai[100];
	strcpy(buffer_ent,"uv4l --driver raspicam --auto-video_nr --width 640 --height 480 --encoding jpeg");
	//puts(buffer_ent);
	system(buffer_ent);
	usleep(500000);
	strcpy(buffer_sai,"dd if=/dev/video0 of=uv4image.jpeg bs=11M count=1");
	//puts(buffer_sai);
	system(buffer_sai);
	usleep(500000);

	strcpy(buffer_ent,"Stream executando...para parar aperte ctrl_c\n");
	puts(buffer_ent);

}
void ctrl_c(int sig)
{
	system("sudo pkill uv4l"); // remove file video%d
	printf("Fechando stream\n");
	//sudo pkill uv4l
	exit(-1);
}
int main(int argc, char *argv[])
{

    //char ch;
    //int fd[2];
    //int fd1[2];
    setup();
    pid_t pfilho;
    signal(SIGINT, ctrl_c);
    signal(SIGUSR1, stream);
    //pipe(fd);
    //pipe(fd1);

    pfilho = fork();

    if(pfilho == 0){
	printf("Processo filho\n");
	   while(1){
     }
    }
    else{
	     while(1){
	        getCM();
		      if(distance1 > 0.0 && distance1 < 1.0){
			         while(stexec==0){
			              usleep(1000);
			              kill(pfilho,SIGUSR1);
			         }
		      }
	    }
    }
    return 0;
}
