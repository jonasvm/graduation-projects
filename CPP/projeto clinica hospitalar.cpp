#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <windows.h>

using namespace std;

struct enfermo // struct do paciente
{
	char Nome[100];
	char Prognostico[1000];
	int Urgencia;
	bool Excluir ;

} dados;

struct enfermo2 // struct de comparaçao
{
	char Nome[100];
	char Prognostico[1000];
	int Urgencia;
	bool Excluir ;
} comparacao;

fstream arquivo;// para fazer operaçoes com arquivos

void cadastrar()
{
	system ("cls");//limpa tudo que tinha da tela antes de entrar nessa funçao

	cout << "\t\t\t\t\t\tCADASTRAR NOVO PACIENTE" << endl << endl << endl;
	cout << "Nome do paciente : ";
	cin.ignore();
	cin.getline(dados.Nome, 100);
	cout << endl;
	cout << "Entre com o prognostico : ";
	cin.getline(dados.Prognostico, 1000);
	cout << endl;
	do
	{
		cout << "Qual o estado de urgencia em que o paciente se encontra? " << endl;
		cout << endl;
		cout << "\t\t1 - Muito grave, atendimento instantaneo" << endl;
		cout << "\t\t2 - Grave, atendimento em 2 horas" << endl;
		cout << "\t\t3 - Medio, atendimento em 4 horas" << endl;
		cout << "\t\t4 - Leve, atendimento por ordem de chegada" << endl;
		cin >> dados.Urgencia;
	}
	while( dados.Urgencia <= 1 && dados.Urgencia >= 4); // para se ele entrar com um valor diferente daqueles mostrados repetir a pergunta	
		
	dados.Excluir = false; // para, em excluir poder verificar se tem ou nao um arquivo para excluir

	arquivo.seekp(0, arquivo.end); // para posicionar o cursor no final do arquivo
	arquivo.write((char*)&dados, sizeof(dados)); // para poder escrever no arquivo

	return;
}

void listar()
{
	system("cls");//limpa tudo que tinha da tela antes de entrar nessa funçao

	cout << "\t\t\t\t\t\t\tLista de pacientes :" << endl << endl << endl;


	arquivo.seekg(0, arquivo.beg); // coloca o cursor no inicio do arquivo para poder ler e listar um por um

	while(arquivo.read((char*) &dados, sizeof(dados)))
	{


		if (dados.Excluir == false) // esse false épara que, se o arquivo nao tiver sido excluido, poder mostrar na listagem
		{
			cout << "Nome do paciente :" << endl;
			cout << "\t\t" << dados.Nome << endl;
			cout << "Prognostico do paciente :" << endl;
			cout << "\t\t" << dados.Prognostico << endl;
			cout << "Urgencia do paciente :" << endl;
			cout << "\t\t" << dados.Urgencia << endl << endl << endl;
		}


	}
	cout << endl << endl;

	arquivo.clear();
	system("pause"); // pausa a tela, fazendo a pessoa ter que apertar uma tecla para poder sair da
}

void procurar()
{
	system("cls");//limpa tudo que tinha da tela antes de entrar nessa funçao

	cout << "\t\t\t\t\t\t\tProcure um paciente :" << endl << endl << endl;

	bool procurar = false;

	arquivo.seekg(0, arquivo.beg); // coloca o cursor no inicio do arquivo

	cout << "\t\tDigite o nome do paciente" << endl;
	cout << "\t";
	cin.ignore();
	cin.getline(comparacao.Nome, 100); // ele entra com o nome para comparaçao

	while(arquivo.eof() == false)
	{
		arquivo.read((char*) &dados, sizeof(dados)); // para poder ler a struct no arquivo

		if(dados.Excluir == false)
		{
			if (arquivo.eof() == false && strcmp(comparacao.Nome, dados.Nome) == 0) // arquivo.eof = false, enquanto nao chegar no final do arquivo vai ler. strcmp compara o nome colocado com o nome da ficha do paciente, se encontrar mosta a ficha do paciente e se nao encontrar mostra a mensagem de nao encontrado
			{
				cout << "Nome do paciente :" << endl;
				cout << "\t\t" << dados.Nome << endl;
				cout << "Prognostico do paciente :" << endl;
				cout << "\t\t" << dados.Prognostico << endl;
				cout << "Urgencia do paciente :" << endl;
				cout << "\t\t" << dados.Urgencia << endl << endl << endl;
				procurar = true; // se achou o arquivo, recebe true para nao mostrar a mensagem
			}
		}

	}
	if(procurar == false) // se nao achou entra nesse if, ja que no if acima recebeu o valor true
	{
		cout << "Paciente nao encontrado" << endl;
	}
	cout << endl << endl;

	arquivo.clear();
	system("pause");


}

void editar()
{
	int CONT;
	system("cls");
	arquivo.seekg(0, arquivo.beg); // coloca o cursor no inicio do arquivo
	cin.ignore();
	cout << "\t\t\t\t\tAlterar dados do paciente" << endl << endl << endl;
	cout << "Qual o nome do paciente que deseja editar? " << endl;
	cout << "\t";
	cin.getline(comparacao.Nome, 100);
	CONT = 0;
	while(arquivo.read((char*) &dados, sizeof(dados))) // enquanto nao chegar no final do arquivo vai salvar no arquivo as novas informaçoes
	{
		if(strcmp(comparacao.Nome, dados.Nome) == 0 && dados.Excluir == false)// strcmp compara o nome colocado com o nome das fichas dos pacientes
		{
			cout << endl;
			cout << "Entre com o novo nome : ";
			cin.getline(dados.Nome, 100);
			cout << endl;
			cout << "Entre com o novo prognostico prognostico : ";
			cin.getline(dados.Prognostico, 1000);
			cout << endl;
			
			do
			{
				cout << "Qual o estado de urgencia em que o paciente se encontra? " << endl;
				cout << endl;
				cout << "\t\t1 - Muito grave, atendimento instantaneo" << endl;
				cout << "\t\t2 - Grave, atendimento em 2 horas" << endl;
				cout << "\t\t3 - Medio, atendimento em 4 horas" << endl;
				cout << "\t\t4 - Leve, atendimento por ordem de chegada" << endl;
				cin >> dados.Urgencia;
			}
			while( dados.Urgencia <= 1 && dados.Urgencia >= 4);
			CONT++;
			arquivo.seekp( arquivo.tellp() - sizeof(dados));
			arquivo.write((char*) &dados, sizeof(dados));
			//Podemos interpretar o exemplo da seguinte forma: Em relação ao começo do arquivo, vá até a posição atual do cursor de escrita e volte uma posição,
			// depois sobrescreva a struct lida
		}

	}
	if(CONT == 0)
	{
		cout << "Paciente nao encontrado" << endl;
	}
	arquivo.clear();
	system("pause");
}

void excluir()
{
	system("cls");

	char op;
	int cont = 0;
	int cont2 = 0;
	
	arquivo.seekg(0, arquivo.beg);// posiciona o curcor no inicio do arquivo

	cout << "\t\t\t\t\tExluisao de ficha do paciente" << endl << endl << endl;

	cout << "\t\Digite o nome do paciente :" << endl;
	cout << "\t\t";
	cin.ignore();
	cin.getline(comparacao.Nome, 100);

	while ( arquivo.eof() == false) // enquanto nao chegar no final do arquivo continuar
	{
		arquivo.read((char*) &dados, sizeof(dados)); // vai ficar lendo as structs do arquivo

		if(arquivo.eof() == false && strcmp(comparacao.Nome, dados.Nome) == 0 && dados.Excluir == false)
		{
			cout << "Deseja realmente excluir a ficha deste paciente? (s/n)" << endl;

			cin >> op;
			if(op == 's' || op == 'S')
			{
				dados.Excluir = true;
				cout << "\t\t\t\t\t  Ficha excluida com sucesso!" << endl << endl << endl;
				arquivo.seekp(arquivo.tellp() - sizeof(dados));// se ele colocar sim vai para o inicio da ficha do paciente escolhido e o preenche com nada, ficando em branco
				arquivo.write((char*) &dados, sizeof(dados));
				cont ++;
				cont2 ++;
			}
			else if( op == 'n' || op == 'N')
			{
			 	cont ++;
			 	cont2 ++;
			    cout << "\t\t\t\t\t  Operacao cancelada com sucesso!" << endl << endl << endl;
			}
			else
			{
				do
				{
					cout << "\t\t\t\tErro! Entre com uma opcao valida!" << endl << endl;
					cout << "Deseja realmente excluir a ficha deste paciente? (s/n)" << endl;

					cin >> op;
					if(op == 's' || op == 'S')
					{
						dados.Excluir = true;
						cout << "\t\t\t\t\t  Ficha excluida com sucesso!" << endl << endl << endl;
						arquivo.seekp(arquivo.tellp() - sizeof(dados));
						arquivo.write((char*) &dados, sizeof(dados));
						cont ++;
						cont2 ++;
					}
					else if( op == 'n' || op == 'N')
					{
					 	cont ++;
					 	cont2 ++;
					    cout << "\t\t\t\t\t  Operacao cancelada com sucesso!" << endl << endl << endl;
					}
					
				}
				while (cont2 == 0);
				
	
			}
		}		
	}
		if (cont == 0)
		{
			cout << endl << endl;
			cout << "\t\t\t\t\t   Paciente nao encontrado" << endl << endl << endl;
		}
			
		


	arquivo.clear();
	system("pause");
}

void navegador()
{
	system("cls");
	int site;
	do
	{
		cout << "\t\t\t\t\tEantre com uma opçao valida" << endl << endl << endl;
		cout << "\t\t1-Entrar pelo navegador Google Chrome" << endl;
		cout << "\t\t2-Entrar pelo navegador Internet Explorer" << endl;
		cout << "\t\t3-Entrar pelo navegador Opera" << endl;
		cout << "\t\t4-Entrar pelo navegador Microsoft Edge" << endl;
		cin >> site;


		switch(site)
		{
		case 1:

			system("start chrome.exe http://www.analisesintomas.com");
			break;
		case 2:

			system("start iexplore.exe http://www.analisesintomas.com");
			break;
		case 3:

			system("start opera.exe http://www.analisesintomas.com");
			break;
		case 4:

			system("start explorer.exe http://www.analisesintomas.com");
			break;
		}
	}
	while(site <= 1 && site >= 4);
}

int main()
{


	system("color 4f");// muda a cor, por isso ficou vermelho o fundo e a letra branca
	int opcao;

	arquivo.open("clinica.txt", ios::in | ios::out | ios::binary);// abre o arquivo chamado clinico

	if(!arquivo.is_open())
	{
		arquivo.open("clinica.txt", ios::in | ios::out | ios::binary | ios::trunc); // se nao tiver o arquivo criado ele cria
	}


	do
	{
		system("cls");
		arquivo.clear();
		cout << "\t\t\t\t\t\tDigite uma opcao valida" << endl << endl << endl << endl << endl << endl;
		cout << "\t\t\t 1-Cadastrar o paciente" << endl;
		cout << "\t\t\t 2-Listar pacientes" << endl;
		cout << "\t\t\t 3-Procurar paciente" << endl;
		cout << "\t\t\t 4-Editar lista" << endl;
		cout << "\t\t\t 5-Excluir ficha de paciente" << endl;
		cout << "\t\t\t 6-Entrar no site de analise de sintomas para um diagnostico" << endl;
		cout << "\t\t\t 7-Sair" << endl;

		cin >> opcao;

		switch(opcao)
		{
		case 1:

			cadastrar();
			break;

		case 2:

			listar();
			break;

		case 3:

			procurar();
			break;

		case 4:

			editar();
			break;

		case 5:

			excluir();
			break;
		case 6:

			navegador();
			break;
		}
	}
	while ( opcao != 7 );



	return 0;
}
