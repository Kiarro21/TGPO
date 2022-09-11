#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

int cmdexec(char *cmd) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	// заполнение структуры нулями
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// запуск дочернего процесса 
	if (CreateProcess(NULL,
		cmd, // команда
		NULL,
		NULL,
		FALSE, // флаг наследования текущего процесса
		0,
		NULL,
		NULL, // текущий диск и каталог
		&si,
		&pi)
		) { // если запуск прошел успешно
		// ждем завершения инициализации
		WaitForInputIdle(pi.hProcess, INFINITE);
		// ждем завершения процесса
		WaitForSingleObject(pi.hProcess, INFINITE);
		// получаем код завершения
		DWORD ec = 0;
		GetExitCodeProcess(pi.hProcess, &ec);
		// закрываем дескриптор процесса
		CloseHandle(pi.hProcess);
		// закрываем дескриптор потока
		CloseHandle(pi.hThread);
		// возвращаем код возврата с приведением к типу int
		return int(ec);
	}
	else {
		cout << "CreateProcess failed " << GetLastError() << endl;
		return 0;
	}
}


int main(int argc, char* argv[])
{
	ifstream inFile(argv[1]);
	ofstream outFile(argv[2]);

	int res = 0;

	while (!inFile.eof()) {
		char in[256] = "", cmd[256] = "mult ";
		inFile.getline(in, 256);
		strcat_s(cmd, in);
		res = cmdexec(cmd);
		outFile << res << endl;
	}

	inFile.close();
	outFile.close();

	system(argv[2]);
	return 0;
}