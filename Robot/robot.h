/*------------------------------
	Robot header
	
	Header Containing:
		Defines,
		Macros,
		Class Predeclarations ,
		and functions definitions; 
	
	Created By: Lucas Martins Mendes
	Date: 18/02/2017 12:45

------------------------------*/

#ifndef ROBOT_H
#define ROBOT_H

//Function Declaration

//Defines
#define 	SSID_HOST 		"RoboAoResgate" 	//Nome da rede wifi quando em modo host
#define 	PASSWORD_HOST 	"aabbccddee" 		//Senha da rede
#define 	SSID_LEN		32 					//Maximium Wireless network name length
#define 	PASSWD_LEN 		32 					//Maximium Wireless network password length


//Class Declaration

RobotClass robot;

//Variable declaration

char * SSID;
char * PASSWORD;
SSID =  (char) malloc(sizeof(char)*SSID_LEN); //aloca 32 caracteres para o nome da rede; malloc --> memory allocate
PASSWORD =  (char) malloc(sizeof(char)*32); //Idem

#endif /* ROBOT_H */
