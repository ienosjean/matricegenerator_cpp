#include <iostream>
#include <fstream>                                 //Criar files
#include <locale>                                  //Necessário para utilizar setlocale
#include "opencv2/highgui/highgui.hpp" 
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

int main()
{

	setlocale(LC_ALL, "Portuguese");               //Habilita acentuação para o português

	fstream fcout("Resultado.dat", ios::out);

	Mat img = imread("OIM.tif");             //Lê os dados da imagem e armazena no objeto 'img'
	
	//**********************TONS DE CINZA
	/*Mat img = imread("OIM.tif",0);
	Mat grey;
	cvtColor(img, grey, CV_BGR2GRAY); */       
	//**********************

		if (img.empty())                         //Tratamento de erro para carregamento da imagem
		{ 
			cout << "A imagem não pôde ser carregada." << endl;
			system("Pause");
			return -1;
		}

		//Cabeçalho para o TecPlot (NÃO ALTERAR)
		fcout << "Title = 'ImageProcess'" << endl;
		fcout << "variables= X, Y, Z, Intensity, Red, Green, Blue" << endl;
		fcout << "zone" << endl;

		//Dados de entrada
		int altura;
		cout << "Digite a altura da amostra: " << endl;
		cin >> altura;

		while (!cin)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Valor Inválido! Digite novamente. \n";
			cin >> altura;
		}

		imshow("Amostra", img);     //Mostra imagem na tela
		waitKey();

		//Atributos coletados em imread() são inseridos nas variáveis x e y
		int x = img.cols;
		int y = img.rows;
		int z = altura;
		int k = altura;

		//Inserção de dados no arquivo (Formato compatível com TecPlot)
		fcout << "T=\" \" " << "   " << "i=" << x << "   " << "j=" << y << "   " << "k=" << z << "   " << "F=point" << " " << endl;
		fcout << " " << endl;



		cout << "Número de linhas: " << x << endl;
		cout << "Número de colunas: " << y << endl;
				
		//Cálculo da Intensidade de Cores
		for (k = 0; k < altura; k++)
		{
			for (int j = 0; j < y; j++)
			{
				for (int i = 0; i < x; i++)
				{
					int R = int((img.at<Vec3b>(Point(i, j))[2]));
					int G = int((img.at<Vec3b>(Point(i, j))[1]));
					int B = int((img.at<Vec3b>(Point(i, j))[0]));

					/*int R = img.at<uchar>(Point(i, j));
					int G = img.at<uchar>(Point(i, j));
					int B = img.at<uchar>(Point(i, j));*/
					
					int intensity = B + (G * 256) + (R * 256 * 256);
					
					fcout << i << " " << -j << " " << k << " " << intensity << " " << R << " " << G << " " << B << endl;
				}
			}
		}
		return 0;
}