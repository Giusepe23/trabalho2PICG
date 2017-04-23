#ifndef __Header__
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void help(void);
void negativo(char* entrada, char* saida);
void limiarizacao(char* entrada, char* saida, int limiar);
void media(int tamanho, char* entrada, char* saida);
void finalizacao(IplImage* original, IplImage* out, char* entrada, char* saida);

void help() {
	cout << "Comandos para ser usados no processador:"
					"./processador media <tamanho_mascara> img_entrada img_saida";
}

void finalizacao(IplImage* img, IplImage* out, char* entrada, char* saida) {
	
	cvNamedWindow("Imagem Original", CV_WINDOW_AUTOSIZE);	
	cvNamedWindow("Imagem de Saida", CV_WINDOW_AUTOSIZE);	
	cvShowImage("Imagem Original", img);
	cvShowImage("Imagem de Saida", out);
	cvSaveImage(saida, out);

	cvWaitKey(0);
}

void media(int tamanho, char* entrada, char* saida) {

	if ((tamanho & 1) == 0) {
		cout << "O tamanho da mascara precisa ser de tamanho impar \n";
		return;
	}

	IplImage* img = cvLoadImage(entrada);

	cout << "Executando o media com mascara "<< tamanho << "x" << tamanho <<" ... \n";
	if (!img) {
		cout << "Imagem de entrada não localizada\n";
		return;
	}

	//Imagem pra guardar o resultado da operação
	IplImage* out = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	
	//O espaço esta relacionado com o tamanho da borda que não sera analizada
	//A mascara ira comecar a analizar de uma certa linha e uma certa coluna em diante.
	//Isso faz com que a mascara caiba dentro da imagem.
	int espaco = (tamanho/2);
	for (int y = espaco; y < (img->height - espaco); y++) {
		uchar* ptr_img = (uchar*)(img->imageData + y * (img->widthStep - espaco));
		uchar* ptr_out = (uchar*)(out->imageData + y * (out->widthStep - espaco));

		for (int x = espaco; x < (img->width + tamanho); x++) {
			int canalR = 0;
			int canalG = 0;
			int canalB = 0;
			/*
			 * Quando a mascara pega um ponto ela vai setar nesse ponto o valor calculado da media
			 * De cada canal, temos que somar todos os valores e dividir pelo tamanho da mascara ao quadrado (tamanho*tamanho)
			 * */
			for (int w = y - espaco; w < y + espaco; w++) {
				uchar* linhaMascara = (uchar*)(img->imageData + w * (img->widthStep - espaco));
				for (int k = x - espaco; k < x + espaco; k++) {
					//Faz a soma de todos os valores nas posicoes da mascara e armazena nos canais 	
					canalR += linhaMascara[3 * k + 2];
					canalG += linhaMascara[3 * k + 1];
					canalB += linhaMascara[3 * k];
				}
			}

			/*uchar r = ptr_img[3 * x + 2];
			uchar g = ptr_img[3 * x + 1];
			uchar b = ptr_img[3 * x];*/
			ptr_out[3 * x] = canalB/(tamanho*tamanho);
			ptr_out[3 * x + 1] = canalG/(tamanho*tamanho);
			ptr_out[3 * x + 2] = canalR/(tamanho*tamanho);
		}
	}

	finalizacao(img, out, entrada, saida);
}

void negativo(char* entrada, char* saida) {

	IplImage* img = cvLoadImage(entrada);

	cout << "Executando o negativo ... \n";
	if (!img) {
		cout << "Imagem de entrada não localizada\n";
		return;
	}

	//Imagem pra guardar o resultado da operação
	IplImage* out = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);


	/* NEGATIVO */
	for (int y = 0; y < img->height; y++) {
		uchar* ptr_img = (uchar*)(img->imageData + y * img->widthStep);
		uchar* ptr_out = (uchar*)(out->imageData + y * out->widthStep);

		for (int x = 0; x < img->width; x++) {
			uchar r = ptr_img[3 * x + 2];
			uchar g = ptr_img[3 * x + 1];
			uchar b = ptr_img[3 * x];
			ptr_out[3 * x] = 255 - 1 - b;
			ptr_out[3 * x + 1] = 255 - 1 - g;
			ptr_out[3 * x + 2] = 255 - 1 - r;
		}
	}
	finalizacao(img, out, entrada, saida);
}

void limiarizacao(char* entrada, char* saida, int limiar) {
	IplImage* img = cvLoadImage(entrada);

	cout << "Executando o limiar ... \n";
	if (!img) {
		cout << "Imagem de entrada não localizada\n";
		return;
	}

	if (limiar > 255 || limiar < 0) {
		cout << "Seu limiar esta fora da faixa 0 <= limiar <+ 255 \n";
		return;
	}

	//Imagem pra guardar o resultado da operação
	IplImage* out = cvCreateImage(
		cvGetSize(img), IPL_DEPTH_8U, 3);
	
	for (int y = 0; y<img->height; y++) {
		uchar* ptr_img = (uchar*)(
			img->imageData + y * img->widthStep);
		uchar* ptr_out = (uchar*)(
			out->imageData + y * out->widthStep);

		for (int x = 0; x<img->width; x++) {
			uchar cor = (ptr_img[3 * x] + ptr_img[3 * x + 1] + ptr_img[3 * x + 2]) / 3;
			if (cor > limiar)
			{

				ptr_out[3 * x] = 255;
				ptr_out[3 * x + 1] = 255;
				ptr_out[3 * x + 2] = 255;
			}
			else {
				ptr_out[3 * x] = 0;
				ptr_out[3 * x + 1] = 0;
				ptr_out[3 * x + 2] = 0;
			}
		}
	}
	finalizacao(img, out, entrada, saida);
}
#endif
