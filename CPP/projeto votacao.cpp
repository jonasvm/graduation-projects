#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <windows.h>

using namespace std;


struct eleitor 
{
	char nome[100];
	char cpf[1000];
	int voto;
	bool Excluir ;

} dados;


struct eleitor_aux 
{
	char nome[100];
	char cpf[1000];
	int voto;
	bool Excluir ;
} comparacao;


fstream arquivo;


void cadastrar()
{
	
	system ("cls");

	cout << "\t\t\t\t\t\tCADASTRAR NOVO ELEITOR" << endl << endl << endl;
	cout << "Nome do Eleitor : ";
	cin.ignore();
	cin.getline(dados.nome, 100);
	cout << endl;
	cout << "CPF do eleitor : ";
	cin.getline(dados.cpf, 1000);
	cout << endl;
	do
	{
		cout << "Escolha um canditato para votar " << endl;
		cout << endl;
		cout << "\t\t1 - Candidato do PT" << endl;
		cout << "\t\t2 - Candidato do PSDB" << endl;
		cout << "\t\t3 - Candidato do PMDB" << endl;
		cout << "\t\t4 - Candidato do PV" << endl;
		cin >> dados.voto;
	}
	while( dados.voto <= 1 && dados.voto >= 4); 	
		
	dados.Excluir = false; 

	arquivo.seekp(0, arquivo.end); 
	arquivo.write((char*)&dados, sizeof(dados)); 

	return;
}


void listar()
{
	system("cls");

	cout << "\t\t\t\t\t\t\tLista de Eleitores e seus votos :" << endl << endl << endl;


	arquivo.seekg(0, arquivo.beg); 

	while(arquivo.read((char*) &dados, sizeof(dados)))
	{


		if (dados.Excluir == false)  
		{
			cout << "Nome do eleitor :" << endl;
			cout << "\t\t" << dados.nome << endl;
			cout << "CPF do eleitor :" << endl;
			cout << "\t\t" << dados.cpf << endl;
			cout << "Voto :" << endl;
			cout << "\t\t" << dados.voto << endl << endl << endl;
		}


	}
	cout << endl << endl;

	arquivo.clear();
	system("pause"); 
}


void procurar()
{
	system("cls");

	cout << "\t\t\t\t\t\t\tProcure um eleitor :" << endl << endl << endl;

	bool procurar = false;

	arquivo.seekg(0, arquivo.beg); 

	cout << "\t\tDigite o nome do eleitor" << endl;
	cout << "\t";
	cin.ignore();
	cin.getline(comparacao.nome, 100); 

	while(arquivo.eof() == false)
	{
		arquivo.read((char*) &dados, sizeof(dados)); 

		if(dados.Excluir == false)
		{
			if (arquivo.eof() == false && strcmp(comparacao.nome, dados.nome) == 0)   
					                                                                
			{  
			    cout << "Nome do eleitor :" << endl;                                                                  
				cout << "\t\t" << dados.nome << endl;
				cout << "CPF do eleitor :" << endl;
				cout << "\t\t" << dados.cpf << endl;
				cout << "Voto do eleitor :" << endl;
				cout << "\t\t" << dados.voto << endl << endl << endl;
				procurar = true; 
			}
		}

	}
	if(procurar == false) 
	{
		cout << "Eleitor nao encontrado" << endl;
	}
	cout << endl << endl;

	arquivo.clear();
	system("pause");


}


void editar()
{
	int CONT;
	system("cls");
	arquivo.seekg(0, arquivo.beg); 
	cin.ignore();
	cout << "\t\t\t\t\tAlterar dados do eleitor" << endl << endl << endl;
	cout << "Qual o cpf do eleitor que deseja editar? " << endl;
	cout << "\t";
	cin.getline(comparacao.cpf, 100);
	CONT = 0;
	while(arquivo.read((char*) &dados, sizeof(dados))) 
	{
		if(strcmp(comparacao.nome, dados.nome) == 0 && dados.Excluir == false)
		{
			cout << endl;
			cout << "Entre com o novo nome : ";
			cin.getline(dados.nome, 100);
			cout << endl;
			cout << "Entre com o novo CPF : ";
			cin.getline(dados.cpf, 1000);
			cout << endl;
			
			do
			{
				cout << "Qual a nova opção para o voto? " << endl;
				cout << endl;
                cout << "\t\t1 - Candidato do PT" << endl;
                cout << "\t\t2 - Candidato do PSDB" << endl;
		        cout << "\t\t3 - Candidato do PMDB" << endl;
                cout << "\t\t4 - Candidato do PV" << endl;
				cin >> dados.voto;
			}
			while( dados.voto <= 1 && dados.voto >= 4);
			CONT++;
			arquivo.seekp( arquivo.tellp() - sizeof(dados));
			arquivo.write((char*) &dados, sizeof(dados));
			
			
		}

	}
	if(CONT == 0)
	{
		cout << "Eleitor nao encontrado" << endl;
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
	
	arquivo.seekg(0, arquivo.beg);

	cout << "\t\t\t\t\tExclusao de eleitor" << endl << endl << endl;

	cout << "\t\Digite o cpf do eleitor :" << endl;
	cout << "\t\t";
	cin.ignore();
	cin.getline(comparacao.cpf, 100);

	while ( arquivo.eof() == false) 
	{
		arquivo.read((char*) &dados, sizeof(dados)); 

		if(arquivo.eof() == false && strcmp(comparacao.cpf, dados.cpf) == 0 && dados.Excluir == false)
		{
			cout << "Deseja realmente excluir o cadastro deste eleitor? (s/n)" << endl;

			cin >> op;
			if(op == 's' || op == 'S')
			{
				dados.Excluir = true;
				cout << "\t\t\t\t\t  Cadastro excluido com sucesso!" << endl << endl << endl;
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
			else
			{
				do
				{
					cout << "\t\t\t\tErro! Entre com uma opcao valida!" << endl << endl;
					cout << "Deseja realmente excluir o cadastro do eleitor? (s/n)" << endl;

					cin >> op;
					if(op == 's' || op == 'S')
					{
						dados.Excluir = true;
						cout << "\t\t\t\t\t  Cadastro excluido com sucesso!" << endl << endl << endl;
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
			cout << "\t\t\t\t\t   Eleitor nao encontrado" << endl << endl << endl;
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
		cout << "\t\t\t\t\tEscolha o site do seu partido para obter mais informações!" << endl << endl << endl;
		cout << "\t\t1-Seguir para o site do PT" << endl;
		cout << "\t\t2-Seguir para o site do PSDB" << endl;
		cout << "\t\t3-Seguir para o site do PMDB" << endl;
		cout << "\t\t4-Seguir para o site do PV" << endl;
		cin >> site;


		switch(site)
		{
		case 1:

			system("start iexplore.exe http://www.pt.org.br");
			break;
		case 2:

			system("start iexplore.exe http://www.psdb.org.br");
			break;
		case 3:

			system("start iexplore.exe http://www.pmdb.org.br/");
			break;
		case 4:

			system("start iexplore.exe http://www.pv.org.br");
			break;
		}
	}
	while(site <= 1 && site >= 4);
}

int main()
{
	

	system("color 0f");
	int opcao;

	arquivo.open("eleitores.txt", ios::in | ios::out | ios::binary);

	if(!arquivo.is_open())
	{
		arquivo.open("eleitores.txt", ios::in | ios::out | ios::binary | ios::trunc); 
	}


	do
	{
		system("cls");
		arquivo.clear();
		cout << "\t\t\t\t\t\tDigite uma opcao valida" << endl << endl << endl << endl << endl << endl;
		cout << "\t\t\t BEM VINDO AO SISTEMA DE VOTOS ELETRONICOS" << endl;
		cout << "\t\t\t 1 - Cadastrar um eleitor" << endl;
		cout << "\t\t\t 2 - Listar eleitores" << endl;
		cout << "\t\t\t 3 - Procurar eleitor" << endl;
		cout << "\t\t\t 4 - Editar eleitor" << endl;
		cout << "\t\t\t 5 - Excluir eleitor" << endl;
		cout << "\t\t\t 6 - Entrar no site dos partidos dos candidatos" << endl;
		cout << "\t\t\t 7 - Sair" << endl;

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