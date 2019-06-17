#include <string.h>
#include <iostream>
#include <stack> 
#include <cstdlib>
#include <sstream>
using namespace std;
string palabraRes="";
int tokensEncontrados [36]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int erroresEncontrados [7]={0,0,0,0,0,0,0};
stack <string> operandos;
stack <string> operadores;
stack <string> tiposOperandos;
stack <string> temporal;
stack <int> saltos;
stack <string> valorOperandos;
stack <float> valroencasodequesalgadecimal;
stack <string> tiposTemporal;
string tablaSimbolos[50][3];
int contF=0,contC=0;
bool insertIdent=false,insertValor=false,declaracion=true;
string cuadruplos[50][4];
int contCuad=0;

//Crea una variable de tipo FILE para trabajar con el documento establecido
FILE *flujo =fopen("archivo.txt","rb");
int feof(FILE *flujo);

char car;
bool rescatado=false;	
bool final=false;



	

string generarCuadruplo(string operador,string op1, string op2){
	int opNum1,opNum2,res;
	string tempoValor;
	opNum1=atoi(op1.c_str());
	opNum2=atoi(op2.c_str());
	if(operador=="+"){
		res=opNum1+opNum2;
	}
	if(operador=="*"){
		res=opNum1*opNum2;
	}
	string resultado;
	std::ostringstream ostr;
	ostr<<res;
	resultado = ostr.str();
	
	cuadruplos[contCuad][0]=operador;
	cuadruplos[contCuad][1]=op1;
	cuadruplos[contCuad][2]=op2;
	cuadruplos[contCuad][3]=resultado;
	
	cout<<"\nResultado: "<<cuadruplos[contCuad][3]<<"\n";
	
	
	tempoValor=resultado;
	contCuad++;
	return tempoValor;
}


void accionesPilaOperandos (int accion ,string operando, string valor ) {
	string operador,op1,op2;
	string tempValor;
	if (accion == 0){
		
		operandos.push(operando);
		valorOperandos.push(valor);
		if(!operadores.empty()){
			if(operadores.top()=="+"||operadores.top()=="*"){
				
				operandos.pop();
				operandos.pop();
				operador=operadores.top();
				operadores.pop();
				op1=valorOperandos.top();
				valorOperandos.pop();
				op2=valorOperandos.top();
				valorOperandos.pop();
				tempValor=generarCuadruplo(operador,op1,op2);
				string temp=temporal.top();
				temporal.pop();
				accionesPilaOperandos(0,temp,tempValor);
			}
		}
	
	}

}

							   
	int matrizPred[46][48]={   //0	1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47
							   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//0
							   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//1
							   {-1,-1,-1,-1,-1,-1,-1,-1, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//2
							   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 5, 5, 5, 5,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//3
							   {-1,-1,-1,-1,-1,-1,-1,-1, 7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 6, 6, 6, 6,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//4
							   { 8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//5
							   {-1,-1,-1,-1,-1,-1,-1, 9,-1,10,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//6
							   {11,12,-1,11,11,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,11,-1,-1,-1,-1,11,11,-1,11,11,11,11,11,11,11,-1},//7
							   {14,14,13,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,-1,-1,-1,-1,14,13,-1,14,13,13,14,13,14,14,-1},//8
							   {-1,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//9
							   {16,22,22,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,22,-1,-1,-1,-1,19,22,-1,17,22,22,18,22,20,21,-1},//10
							   {-1,-1,-1,-1,-1,-1,-1,23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//11
							   {24,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//12
							   {-1,-1,-1,-1,26,25,26,26,-1,26,26,26,-1,26,26,26,26,26,26,26,26,26,26,26,26,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//13
							   {-1,-1,-1,-1,-1,27,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//14
							   {28,-1,-1,28,-1,-1,-1,-1,-1,-1,-1,-1,28,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,28,28,28,28,28,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//15
							   {-1,-1,-1,-1,-1,-1,30,-1,-1,29,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//16
							   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,31,32,33,34,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//17
							   {35,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//18
							   {-1,-1,-1,-1,-1,37,-1,36,-1,36,-1,-1,-1,86,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//19
							   {-1,-1,-1,-1,-1,38,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//20
							   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,39,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//21
							   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,40,-1,-1,-1,-1,-1,-1,-1},//22
							   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,41,42,-1,-1,-1,-1,-1},//23
							   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,43,-1,-1,-1,-1},//24
							   {44,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//25
							   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,45,-1,-1},//26
							   {46,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//27
							   {-1,-1,-1,-1,48,-1,-1,-1,-1,47,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//28
							   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,49,-1},//29
							   {50,-1,-1,50,-1,-1,-1,-1,-1,-1,-1,-1,50,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,50,50,50,50,50,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//30
							   {-1,-1,-1,-1,52,-1,-1,-1,-1,51,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//31
							   {53,-1,-1,53,-1,-1,-1,-1,-1,-1,-1,-1,53,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,53,53,53,53,53,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//32
							   {-1,-1,-1,-1,55,-1,55,55,-1,55,54,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//33
							   {56,-1,-1,56,-1,-1,-1,-1,-1,-1,-1,-1,56,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,56,56,56,56,56,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//34
							   {-1,-1,-1,-1,58,-1,58,58,-1,58,58,57,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//35
							   {60,-1,-1,60,-1,-1,-1,-1,-1,-1,-1,-1,59,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,60,60,60,60,60,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//36
							   {61,-1,-1,61,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,61,61,61,61,61,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//37
							   {-1,-1,-1,-1,63,-1,63,63,-1,63,63,63,-1,-1,-1,-1,-1,-1,-1,62,62,62,62,62,62,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//38
							   {64,-1,-1,64,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,64,64,64,64,64,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//39
							   {-1,-1,-1,-1,65,-1,65,65,-1,65,65,65,-1,-1,66,67,-1,-1,-1,65,65,65,65,65,65,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//40
							   {68,-1,-1,68,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,68,68,68,68,68,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//41
							   {-1,-1,-1,-1,72,-1,72,72,-1,72,72,72,-1,-1,72,72,69,70,71,72,72,72,72,72,72,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//42
							   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,73,74,75,76,77,78,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//43
							   {79,-1,-1,85,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,80,81,82,83,84,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//44
							   {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,87,-1,-1,-1,88,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
	};
	int matrizProd[88][8]={
							{1030,1003,1000,1004,1001,3,2,1002},//1
							{1031,8,1032},//2
							{1008,4,1008},//3
							{},//4
							{18,6,1007,5},//5
							{4},//6
							{},//7
							{19,7},//8
							{},//9
							{1009,6},//10
							{11,9},//11
							{10,9},//12
							{},//13
							{8},//14
							{1001,8,1002},//15
							{26,12},//16
							{23,12},//17
							{25,12},//18
							{22,12},//19
							{27,12},//20
							{30,12},//21
							{},//22
							{1007,11},//23
							{1000,14},//24
							{15},//25
							{},//26
							{1005,16,1006},//27
							{33,17},//28
							{1009,16},//29
							{},//30
							{1033},//31
							{1034},//32
							{1035},//33
							{1036},//34
							{1000,20},//35
							{},//36
							{21},//37
							{1005,1025,1006,20},//38
							{1037,8,1038,1003,33,1004,1039},//39
							{1040,1003,33,1004,8,24,1042},//40
							{1041,8},//41
							{},//42
							{1043,1003,33,1004,8,1044},//43
							{13,1013,33},//44
							{1045,1003,28,1004},//45
							{1000,29},//46
							{1009,28},//47
							{},//48
							{1046,1003,31,1004},//49
							{33,32},//50
							{1009,31},//51
							{},//52
							{35,34},//53
							{1010,33},//54
							{},//55
							{37,36},//56
							{1011,35},//57
							{},//58
							{1012,58},//59
							{38},//60
							{40,39},//61
							{44,40},//62
							{},//63
							{42,41},//64
							{},//65
							{1014,40},//66
							{1015,40},//67
							{45,43},//68
							{1016,42},//69
							{1017,42},//70
							{1018,42},//71
							{},//72
							{1019},//73
							{1020},//74
							{1021},//75
							{1022},//76
							{1023},//77
							{1024},//78
							{13},//79
							{1025},//80
							{1026},//81
							{1027},//82
							{1028},//83
							{1029},//84
							{1003,33,1004},//85
							{1013,46},//86*
							{1025},//87*
							{1029}//88*
	};

//Imprime los errores encontrados
int error(int edo){
	switch(edo){
		case 500:
			cout<<"Formato de numero real incorrecto";
			erroresEncontrados[0]=erroresEncontrados[0]+1;
		break;
		case 501:
			cout<<"Formato de numero con notacion cientifica incorrecto";
			erroresEncontrados[1]=erroresEncontrados[1]+1;
		break;	
		case 502:
			cout<<"Dos comillas sencillas seguidas";
			erroresEncontrados[2]=erroresEncontrados[2]+1;
		break;
		case 503:
			cout<<"Formato de constante caracter invalido";
			erroresEncontrados[3]=erroresEncontrados[3]+1;
		break;
		case 504:
			cout<<"Error en operador logico AND";
			erroresEncontrados[4]=erroresEncontrados[4]+1;
		break;
		case 505:
			cout<<"Error en operador logico OR";
			erroresEncontrados[5]=erroresEncontrados[5]+1;
		break;	
		case 506:
			cout<<"Valor inicial ingresado invalido";
			erroresEncontrados[6]=erroresEncontrados[6]+1;
		break;
	}
	return edo;
}

//ASIGNA UN NÚMERO A CADA ELEMENTO DETECTADO Y LE AUMENTA 1 A SU RESPECTIVO CONTADOR
int token(int edo){
	int elem=1506;
	switch(edo){
		case 100:
			cout<<"Palabra reservada";
			tokensEncontrados[0]=tokensEncontrados[0]+1;			
			rescatado=true;
			if(palabraRes=="constructor")
					elem=1030;
			if(palabraRes=="commit")
					elem=1031;
			if(palabraRes=="end")
					elem=1032;
			if(palabraRes=="int")
					elem=1033;
			if(palabraRes=="float")
					elem=1034;
			if(palabraRes=="char")
					elem=1035;
			if(palabraRes=="string")
					elem=1036;
			if(palabraRes=="do")
					elem=1037;
			if(palabraRes=="dowhile")
					elem=1038;
			if(palabraRes=="enddo")
					elem=1039;
			if(palabraRes=="if")
					elem=1040;
			if(palabraRes=="else")
					elem=1041;
			if(palabraRes=="endif")
					elem=1042;
			if(palabraRes=="while")
					elem=1043;
			if(palabraRes=="endwhile")
					elem=1044;
			if(palabraRes=="read")
					elem=1045;
			if(palabraRes=="write")
					elem=1046;
			break;
		case 101:
			cout<<"Identificador";
			tokensEncontrados[1]=tokensEncontrados[1]+1;
			rescatado=true;
			elem=1000;
			break;
		case 102:
			cout<<"Numero entero";
			tokensEncontrados[2]=tokensEncontrados[2]+1;
			rescatado=true;
			elem=1025;
			break;
		case 103:
			cout<<"Numero real";
			tokensEncontrados[3]=tokensEncontrados[3]+1;
			rescatado=true;
			elem=1026;
			break;
		case 104:
			cout<<"Notacion cientifica";
			tokensEncontrados[4]=tokensEncontrados[4]+1;
			rescatado=true;
			elem=1027;
			break;
		case 105:
			cout<<"Constante caracter";
			tokensEncontrados[5]=tokensEncontrados[5]+1;
			elem=1028;
			break;
		case 106:
			cout<<"Constante string";
			tokensEncontrados[6]=tokensEncontrados[6]+1;
			elem=1029;
			break;						
		case 107:
			cout<<"Signo de suma";
			tokensEncontrados[7]=tokensEncontrados[7]+1;
			elem=1014;
			break;
		case 108:
			cout<<"Signo de resta";
			tokensEncontrados[8]=tokensEncontrados[8]+1;
			elem=1015;
			break;
		case 109:
			cout<<"Signo de multiplicacion";
			tokensEncontrados[9]=tokensEncontrados[9]+1;
			elem=1016;
			break;
		case 110:
			cout<<"Signo de division";
			tokensEncontrados[10]=tokensEncontrados[10]+1;
			elem=1017;
			break;
		case 111:
			cout<<"Signo de modular";
			tokensEncontrados[11]=tokensEncontrados[11]+1;
			elem=1018;
			break;
		case 112:
			cout<<"Operador logico AND";
			tokensEncontrados[12]=tokensEncontrados[12]+1;
			elem=1011;
			break;
		case 113:
			cout<<"Operador logico NOT";
			tokensEncontrados[13]=tokensEncontrados[13]+1;
			rescatado=true;
			elem=1012;
			break;
		case 114:
			cout<<"Operador logico Diferente";
			tokensEncontrados[14]=tokensEncontrados[14]+1;
			elem=1020;
			break;
		case 115:
			cout<<"Operador logico OR";
			tokensEncontrados[15]=tokensEncontrados[15]+1;
			elem=1010;
			break;
		case 116:
			cout<<"Asignacion";
			tokensEncontrados[16]=tokensEncontrados[16]+1;
			rescatado=true;
			elem=1013;
			break;
		case 117:
			cout<<"Igual que";
			tokensEncontrados[17]=tokensEncontrados[17]+1;
			elem=1019;
			break;
		case 118:
			cout<<"Mayor que";
			tokensEncontrados[18]=tokensEncontrados[18]+1;
			rescatado=true;
			elem=1023;
			break;
		case 119:
			cout<<"Mayor e igual que";
			tokensEncontrados[19]=tokensEncontrados[19]+1;
			elem=1024;
			break;
		case 120:
			cout<<"Menor que";
			tokensEncontrados[20]=tokensEncontrados[20]+1;
			rescatado=true;
			elem=1021;
			break;
		case 121:
			cout<<"Menor e igual que";
			tokensEncontrados[21]=tokensEncontrados[21]+1;
			elem=1022;
			break;
		case 122:
			cout<<"Parentesis de apertura";
			tokensEncontrados[22]=tokensEncontrados[22]+1;
			elem=1003;
			break;
		case 123:
			cout<<"Corchete de apertura";
			tokensEncontrados[23]=tokensEncontrados[23]+1;
			elem=1005;
			break;
		case 124:
			cout<<"Llave de apertura";
			tokensEncontrados[24]=tokensEncontrados[24]+1;
			elem=1001;
			break;												
		case 125:
			cout<<"Coma";
			tokensEncontrados[25]=tokensEncontrados[25]+1;
			elem=1009;
			break;
		case 126:
			cout<<"Punto";
			tokensEncontrados[26]=tokensEncontrados[26]+1;
			break;
		case 127:
			cout<<"Dos puntos";
			tokensEncontrados[27]=tokensEncontrados[27]+1;
			elem=1008;
			break;
		case 128:
			cout<<"Punto y coma";
			tokensEncontrados[28]=tokensEncontrados[28]+1;
			elem=1007;
			break;
		case 129:
			cout<<"Comentario";
			tokensEncontrados[29]=tokensEncontrados[29]+1;
			break;
		case 130:
			cout<<"Espacio en blanco";
			tokensEncontrados[30]=tokensEncontrados[30]+1;
			elem=200;
			break;
		case 131:
			cout<<"Tabulador";
			tokensEncontrados[31]=tokensEncontrados[31]+1;
			break;
		case 132:
			cout<<"Enter";
			tokensEncontrados[32]=tokensEncontrados[32]+1;
			elem=200;
			break;	
		case 133:
			cout<<"Parentesis de cierre";
			tokensEncontrados[33]=tokensEncontrados[33]+1;
			elem=1004;
			break;
		case 134:
			cout<<"Corchete de cierre";
			tokensEncontrados[34]=tokensEncontrados[34]+1;
			elem=1006;
			break;
		case 135:
			cout<<"Llave de cierre";
			tokensEncontrados[35]=tokensEncontrados[35]+1;
			elem=1002;
			break;								
	}
	return elem;
}

//ASIGNA UN VALOR A LOS CARACTERES LEÍDOS DEL DOCUMENTO PARA COMPARARLO EN EL OJO DE AGAMMOTTO
int relaciona(char car){

	if(car>='A'&&car<='Z'&&car!='E' || car>='a'&&car<='z'&&car!='e'){
	//if(car>='A'&&car<='Z'|| car>='a'&&car<='z'){
		return 0; //Columna de letras
	}
	if(car>='0'&&car<='9'){		
		return 1; //Columna de dígitos
	}
	switch(car){
		case '_':
			return 2;
		break;
		case 'E':
			return 3;
		break;
		case 'e':
			return 4;
		break;
		case '.':
			return 5;
		break;
		case '\'': //Columna de comilla sencilla
			return 6;
		break;
		case '\"': //Columna de comilla doble
			return 7;
		break;
		case '&':
			return 8;
		break;
		case '!':
			return 9;
		break;
		case '=':
			return 10;
		break;
		case '|':
			return 11;
		break;
		case '>':
			return 12;
		break;
		case '<':
			return 13;
		break;
		case '(':
			return 14;
		break;
		case ')':
			return 15;
		break;
		case '[':
			return 16;
		break;
		case ']':
			return 17;
		break;
		case '{':
			return 18;
		break;
		case '}':
			return 19;
		break;
		case '+':
			return 20;
		break;
		case '-':
			return 21;
		break;
		case '*':
			return 22;
		break;
		case '/':
			return 23;
		break;
		case '%':
			return 24;
		break;
		case ',':
			return 25;
		break;
		case ':':
			return 26;
		break;
		case ';':
			return 27;
		break;
		case '#':
			return 28;
		break;
		case ' ': //Columna de espacio en blanco
			return 29;
		break;
		case '\t': //Columna de tabulación derecha
			return 30;
		break;
		case '\n': //Columna de salto de línea
			return 31;
		break;
		
	}
	
	return 0;
}

//LEE EL ARCHIVO Y EXTRAE UN CARACTER
char lecturaDeArchivo(){
    if(flujo == NULL){
        perror("Error en la apertura de archivo");
    }
    char caracter;
	
	//CUANDO TERMINA DE LEER, DEVUELVE UN $ PARA INDICARLO
    if(feof(flujo)!=0){
    	
    	final=true;
		return '$';
	}
	else{
        caracter = fgetc(flujo);
        cout<<"_"<<caracter<<"_"<<"\n";
        return caracter;
 	}
}

int verificarExist(string id){
	int posicion=-1;
	for(int i=0;i<50;i++){
		if(tablaSimbolos[i][1]==id){
			posicion=i;
		}
	}
	return posicion;
}

//Analiza si el caracter es terminal o de transición y devuelve elementos terminales al analizador Sintáctico
int analiza(){
	int edo,col,posVar;
	char numeroDescompuesto [20];
	char cadDescompuesto[20];
	string numero,identificador="",conString;
	int contCharNum=0,contCharCad=0;
	int m[18][32]={{1,3,506,1,1,126,9,11,12,13,15,14,16,17,122,133,123,134,124,135,107,108,109,110,111,125,127,128,129,130,131,132},
	{1,2,2,1,1,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100},
	{2,2,2,1,1,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101},
	{102,3,102,102,102,4,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102},
	{500,5,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500,500},
	{103,5,103,6,6,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103},
	{501,8,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,7,7,501,501,501,501,501,501,501,501,501,501},
	{501,8,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501,501},
	{104,8,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104},
	{10,10,10,10,10,10,502,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10},
	{503,503,503,503,503,503,105,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503,503},
	{11,11,11,11,11,11,11,106,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11},
	{504,504,504,504,504,504,504,504,112,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504,504},
	{113,113,113,113,113,113,113,113,113,113,114,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113},
	{505,505,505,505,505,505,505,505,505,505,505,115,505,505,505,505,505,505,505,505,505,505,505,505,505,505,505,505,505,505,505,505},
	{116,116,116,116,116,116,116,116,116,116,117,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116},
	{118,118,118,118,118,118,118,118,118,118,119,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118},
	{120,120,120,120,120,120,120,120,120,120,121,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120}};
	edo=0;
	while(edo<=17){
		if(car==' '||car=='\n'){
			rescatado=false;
			palabraRes="";
		}
		if(rescatado&&(car!=' '||car!='\n'))
		{
			//cout<<"Se rescató un caracter: "<<"_"<<car<<"_";
			rescatado=false;
			palabraRes="";		
			
		}
		else{
			car=lecturaDeArchivo();
		}
		if(car=='$'){
			col=relaciona(')');
			edo=m[edo][col];
		}
		else{
			
		col=relaciona(car);
		
		edo=m[edo][col];
		if(edo==1){
			palabraRes=palabraRes+car;
		}
		if(edo==2)
			palabraRes="";
		}
		
		//Si se encuentra dígitos en el archivo, los añade a un arreglo con los dígitos, para formar un número 
		if(car>='0'&&car<='9'){		
			numeroDescompuesto[contCharNum]=car;
			contCharNum++;
		}
		
		//Si se encuentra letras en el archivo, los añade a un arreglo con las letras para formar las palabras entre comillas
		if(car>='A'&&car<='Z' || car>='a'&&car<='z'){
			cadDescompuesto[contCharCad]=car;
			contCharCad++;
		}
		
		//Si se encuentra letras, dígitos o _ en el archivo, los añade a un arreglo para formar los identificadores
		if(car>='A'&&car<='Z' || car>='a'&&car<='z' || car=='_'||car>='0'&&car<='9'){
			identificador=identificador+car;
		}
	}
	
	//Retorna el último elemento de la cadena $
	if(final){
		return 1047;
	}
	
	//Retorna estados de aceptación
	if(edo>=100&&edo<=135){
		
		
		cout<<"\n"<<edo;
		
		cout<<palabraRes<<"\n";
		int elemento=token(edo);
		if(elemento==1033||elemento==1036){
			tablaSimbolos[contF][contC]=palabraRes;
			insertIdent=true;
			contC++;
			return elemento;
		}
		
		//Si la sucesión de caracteres, es un número entero, lo almacena en una cadena
		
		if(edo==102){
			numero=string(numeroDescompuesto,contCharNum);
			cout<<"\nNumero: "<<numero<<"\n";
		}
		
		
		//Si se encuentra un identificdor y ya no es de la parte de declaración, realiza las acciones correspondientes c:
		if(edo==101&&!declaracion){
		
			posVar=verificarExist(identificador);
			if(posVar>=0)
			{
				cout<<"\nVariable declarada";
				accionesPilaOperandos(0,identificador,tablaSimbolos[posVar][2]);
				
				
			} else {
				cout<<"\nVariable no declarada jaja";
				return 500; //Regresa este valor para que termine el programa.
			}
		}
		
		if (edo==107){
			operadores.push("+");	
		}
		
		if (edo==109){
			operadores.push("*");
		}
		//Si la sucesión de caracteres, es una constante string, lo guarda en un string
		if(edo==106){
			conString=string(cadDescompuesto,contCharCad);
			cout<<"\nConstante String: "<<conString<<"\n";
		}
		
		
		if(insertIdent){
			tablaSimbolos[contF][contC]=identificador;
			insertValor=true;
			insertIdent=false;
			contC++;
			return elemento;
		}
		
		if(insertValor&&(edo==102||edo==106)){
			if(edo==102){
				tablaSimbolos[contF][contC]=numero;
			}
			if(edo==106){
				tablaSimbolos[contF][contC]=conString;
			}
			contF++;
			contC=0;
			insertValor=false;
		}
		
		//Cuando encuentra el COMMIT, la declaración de variables ya terminó
		if(elemento==1031){
			declaracion=false;
		}
		return elemento;
		//cout<<"\n";
		//cout<<palabraRes<<"\n";
	}
	else{
		//Retorna estados de Error
		if(edo>=500&&edo<=506){
			cout<<"Error:";
			cout<<"\n";
			return error(edo);
			
		}

			
	}

}

int main(){
	
	temporal.push("T1");
temporal.push("T2");
temporal.push("T3");
temporal.push("T4");
temporal.push("T5");
	stack <int> pilaEjecucion;
	int posMProd=0,filaMP=0,cont=7;
	pilaEjecucion.push(1047); //$
	pilaEjecucion.push(1);	//program
	
	//Ingresa los primeros elementos de forma inversa en la pila de ejecución
	filaMP=pilaEjecucion.top();
	pilaEjecucion.pop();
	while(cont>=0){	
		posMProd=matrizProd[(filaMP-1)][cont];	
		if(posMProd>0){
			pilaEjecucion.push(posMProd);
		}	
		cont=cont-1;
	}
		
	int elemMPred;


	//Analiza la sintaxis de la expresión
	for(int i=0;i<=100;i++){
		
		bool vacio=true;
		int colMP=analiza();
		cout<<"\nElemento "<<colMP<<"\n";	
		if(colMP>=500&&colMP<=600){
			cout<<"\nError: Corrija el codigo para continuar";
			i=1000;
		}
		while(vacio){ //Mientras no encuentre el elemento terminal en la pila de ejecución
			if(pilaEjecucion.top()>=1000){	
				
				vacio=false;
				if(colMP==pilaEjecucion.top()){	
					pilaEjecucion.pop();
					if(pilaEjecucion.empty()){
						cout<<"\n\nSintaxis correcta\n";
						i=1000;				
					}
					//else
						//cout<<"\nNueva cima:"<<pilaEjecucion.top()<<"\n";
				}
				else{			
					cout<<"\nERROR DE SINTAXIS";
					i=1000;
				}
			}	
			else{
				elemMPred=matrizPred[pilaEjecucion.top()-1][colMP-1000];
				//cout<<"\nF:"<<pilaEjecucion.top()-1<<" Col:"<<colMP-1000<<"\n";
				if(elemMPred<0){
					cout<<"\nERROR DE SINTAXIS";
					i=1000;
					vacio=false;
				}
				else{
					filaMP=elemMPred;
					pilaEjecucion.pop();
					//cout<<"\nNueva cima:"<<pilaEjecucion.top()<<"\n";
					cont=7;
					while(cont>=0){	
													
						posMProd=matrizProd[(filaMP-1)][cont];
						//cout<<"F:"<<filaMP-1<<" Col:"<<cont<<"\n";
						//cout<<"Valor de matriz: "<<posMProd<<"\n";				
						cont=cont-1;
						if(posMProd>0){
							pilaEjecucion.push(posMProd);							
							//cout<<"\nNueva cima:"<<pilaEjecucion.top()<<"\n";
						}
					}
				}
			}
		}
	}
	
	cout<<"\nTipo: "<<tablaSimbolos[1][0]<<"\n";
	cout<<"Identificador: "<<tablaSimbolos[1][1]<<"\n";
	cout<<"Valor: "<<tablaSimbolos[1][2]<<"\n";

	//INDICA CUÁNTOS ELEMENTOS HAY DE CADA TIPO
	
	cout<<"Palabras reservadas: "<<tokensEncontrados[0]<<"\n";
	cout<<"Identificadores: "<<tokensEncontrados[1]<<"\n";
	cout<<"Numeros enteros: "<<tokensEncontrados[2]<<"\n";
	cout<<"Numeros reales: "<<tokensEncontrados[3]<<"\n";
	cout<<"Numeros con notacion cientifica: "<<tokensEncontrados[4]<<"\n";
	cout<<"Constantes caracter: "<<tokensEncontrados[5]<<"\n";
	cout<<"Constantes String: "<<tokensEncontrados[6]<<"\n";
	cout<<"Signos de suma: "<<tokensEncontrados[7]<<"\n";
	cout<<"Signos de resta: "<<tokensEncontrados[8]<<"\n";
	cout<<"Signos de multiplicacion: "<<tokensEncontrados[9]<<"\n";
	cout<<"Signos de division: "<<tokensEncontrados[10]<<"\n";
	cout<<"Signos de operacion modular: "<<tokensEncontrados[11]<<"\n";
	cout<<"Operadores AND: "<<tokensEncontrados[12]<<"\n";
	cout<<"Operadores NOT: "<<tokensEncontrados[13]<<"\n";
	cout<<"Operadores Diferente: "<<tokensEncontrados[14]<<"\n";
	cout<<"Operadores OR: "<<tokensEncontrados[15]<<"\n";
	cout<<"Asignaciones: "<<tokensEncontrados[16]<<"\n";
	cout<<"Igual que: "<<tokensEncontrados[17]<<"\n";
	cout<<"Mayor que: "<<tokensEncontrados[18]<<"\n";
	cout<<"Mayor o igual que: "<<tokensEncontrados[19]<<"\n";
	cout<<"Menor que: "<<tokensEncontrados[20]<<"\n";
	cout<<"Menor o igual que: "<<tokensEncontrados[21]<<"\n";
	cout<<"Parentesis de apertura: "<<tokensEncontrados[22]<<"\n";
	cout<<"Corchetes de apertura: "<<tokensEncontrados[23]<<"\n";
	cout<<"Llaves de apertura: "<<tokensEncontrados[24]<<"\n";
	cout<<"Comas: "<<tokensEncontrados[25]<<"\n";
	cout<<"Puntos: "<<tokensEncontrados[26]<<"\n";
	cout<<"Dos puntos: "<<tokensEncontrados[27]<<"\n";
	cout<<"Punto y coma: "<<tokensEncontrados[28]<<"\n";
	cout<<"Comentarios: "<<tokensEncontrados[29]<<"\n";
	cout<<"Espacios en blanco: "<<tokensEncontrados[30]<<"\n";
	cout<<"Tabulaciones: "<<tokensEncontrados[31]<<"\n";
	cout<<"Enters: "<<tokensEncontrados[32]<<"\n";
	cout<<"Parentesis de cierre: "<<tokensEncontrados[33]<<"\n";
	cout<<"Corchetes de cierre: "<<tokensEncontrados[34]<<"\n";
	cout<<"Llaves de cierre: "<<tokensEncontrados[35]<<"\n";

	return 0;

}



