#include<opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include "header.hpp"

using namespace cv;
using namespace std;

void negativo(char* entrada, char* saida);
void limiarizacao(char* entrada, char* saida, int limiar);

int main(int argc, char** argv) {

	if (argc < 3) {
		cout << "A entrada precisar ter o segunte formato: ./processador <metodo> imagem_entrada imagem_saida\n";
		return -1;
	}
	string metodo = argv[1];

	if (metodo == "negativo") {
		negativo(argv[2], argv[3]);
	} else if (metodo == "limiarizacao") {
		int limiar = stoi(argv[4]);
		limiarizacao(argv[2], argv[3], limiar);
	} else if (metodo == "media") {
		if (argc > 5) {
			help();	
			return -1;
		}
		int tamanho = stoi(argv[2]);
		media(tamanho, argv[3], argv[4]);
	}
	return 1;
}


