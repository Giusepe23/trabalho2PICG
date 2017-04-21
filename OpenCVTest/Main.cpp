#include<opencv2/highgui/highgui.hpp>

using namespace cv;
int limiar = 100;


int main()
{

	IplImage* img = cvLoadImage("lena.png");

	//Imagem pra guardar o resultado da operação
	IplImage* out = cvCreateImage(
		cvGetSize(img), IPL_DEPTH_8U, 3);


	//cria duas janelas
	//CV_WINDOW_AUTOSIZE: janela se expande para mostrar imagem em tamanho real
	//0: cria janela com tamanho fixo  
	cvNamedWindow("Imagem Original", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Imagem de Saida", CV_WINDOW_AUTOSIZE);

	/* NEGATIVO */
	for (int y = 0; y<img->height; y++) {
		uchar* ptr_img = (uchar*)(
			img->imageData + y * img->widthStep);
		uchar* ptr_out = (uchar*)(
			out->imageData + y * out->widthStep);

		for (int x = 0; x<img->width; x++) {
			uchar r = ptr_img[3 * x + 2];
			uchar g = ptr_img[3 * x + 1];
			uchar b = ptr_img[3 * x];
			ptr_out[3 * x] = 255 - 1 - b;
			ptr_out[3 * x + 1] = 255 - 1 - g;
			ptr_out[3 * x + 2] = 255 - 1 - r;
		}
	}
	/**/

	/* LIMIARIZAÇÃO
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
	}*/







	//exibe a imagem img na janela 
	cvShowImage("Imagem Original", img);

	//exibe a imagem out na janela 
	cvShowImage("Imagem de Saida", out);

	//faz com que o programa espere por um evento do teclado
	cvWaitKey(0);

	//destroi janelas
	cvDestroyWindow("Imagem Original");
	cvDestroyWindow("Imagem de Saida");

	//destroi imagem
	cvReleaseImage(&img);
	cvReleaseImage(&out);
	return 1;
}

