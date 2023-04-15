#include"Header.h"

vector<info> vectInf;
vector<infCont> vectCont;
vector<ApplyCont> vectApply;

//FOR INTERFACE
void GoToXY(short x, short y);
void ConsoleCursorVisible(bool show, short size);
void BackAqua();
void White();
void Grey();
void BackBlack();
/////////////////////////////////////////////////

//READ INFORMATION
void ReadAppluCont() {
	fstream apply;
	ApplyCont cont;
	apply.open("statement.txt", fstream::in);
	while (apply >> cont.year) {
		int num = apply.tellp();
		apply.seekp(num + 2);
		getline(apply, cont.name);
		getline(apply, cont.country);
		getline(apply, cont.musicInst);
		vectApply.push_back(cont);
	}
	apply.close();
}
void readInf() {
	fstream inf;
	info info;
	inf.open("inf.txt", fstream::in);
	while (inf >> info.login) {
		inf >> info.password;
		inf >> info.role;
		inf >> info.isActive;
		vectInf.push_back(info);
	}
	inf.close();
}
void readContest() {
	fstream cont;
	infCont contest;
	cont.open("contest.txt", fstream::in);
	while (cont >> contest.year) {
		int num = cont.tellp();
		cont.seekp(num + 2);
		getline(cont, contest.name);
		getline(cont, contest.country);
		getline(cont, contest.musicInst);
		cont >> contest.place;
		cont >> contest.rating;
		vectCont.push_back(contest);
	}
	cont.close();
}

void Apply() {
	ApplyCont cont;
	bool isCorrect;
	int x, y = 7;
	GoToXY(46, y);
	cout << "Пожалуйста, введите ваши данные: " << endl;
	y += 2;
	GoToXY(50, y++);
	cout << "ФИО: ";
	string a;
	a = getchar();
	getline(cin, cont.name);
	if (a != "\n")
		cont.name.insert(0, a);
	
	do {
		GoToXY(50, y);
		cout << "Возраст: ";
		isCorrect = 1;
		cin >> cont.year;
		if (cont.year <= 0 || cont.year >= 100) {
			GoToXY(50, y+1);
			cout << "Возраст введен некорректно." << endl;
			GoToXY(50, y + 1);
			cout << "Повторите попытку." << endl;
			isCorrect = 0;
		}
	} while (isCorrect == 0);
	y++;
	GoToXY(50, y++);
	cout << "Страна: ";
	getchar();
	getline(cin, cont.country);
	GoToXY(50, y++);
	cout << "Музыкальный инструмент: ";
	getline(cin, cont.musicInst);

	vectApply.push_back(cont);
	system("cls");
	GoToXY(40, y);
	cout << "Заявление на участие в конкурсе успешно подано." << endl << endl;
	_getch();
}
int ManagementAccount() {
	int position;
	char choice_ch;
	info person[2];
	string choice_s;
	bool isCheck = 0, isCorrect = 0;
	string menu[] = { "Заблокировать аккаунт", "Разблокировать аккаунт", "Назад" };
	int active_menu = 0;
	while (isCorrect == 0) {
		system("cls");
		int x = 50, y = 10;
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu)
				BackAqua();
			else White();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		GoToXY(x, y++);

		char ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP: {
			if (active_menu > 0)
				--active_menu;
		}
			   break;
		case DOWN: {
			if (active_menu < size(menu) - 1)
				++active_menu;
		}
				 break;
		case ENTER:
			switch (active_menu)
			{
			case 0:
				choice_ch = '1';
				break;
			case 1: {
				choice_ch = '2';
			}
				  break;
			case 2: {
				BackBlack();
				system("cls");
				return 0;
			}
				  break;
			}
			system("cls");
			y = 3;
			White();
			GoToXY(x, y++);
			cout << "______________________________________" << endl;
			GoToXY(x, y++);
			cout << "  Логин                       Роль" << endl;
			y++;

			for (int i = 0; i < vectInf.size() - 1; i++) {
				string role;
				GoToXY(x, y++);
				if (vectInf[i].role == 2)
					role = "Конкурсант";
				else if (vectInf[i].role == 3)
					role = "Пользователь";
				else role = "Администратор";
				cout << setw(27) << left << vectInf[i].login << setw(12) << left << role << setw(1) << endl;
			}
			GoToXY(x, y++);
			cout << "______________________________________" << endl;
			GoToXY(x, y++);
			cout << "Введите имя пользователя: ";
				cin >> person[0].login;
				isCheck = 0;
				for (int i = 0; i < vectInf.size() && isCheck == 0; i++)
					if (vectInf[i].login == person[0].login) {
						isCheck = 1;
						position = i;
					}
				if (isCheck == 1) {
					if (vectInf[position].role == 1) {
						GoToXY(35, y++);
						cout << "Данная операция не может быть проведена с администратором." << endl;
						_getch();
					}
					else
					{
						switch (choice_ch)
						{
						case '1': {
							vectInf[position].isActive = 0;
							GoToXY(x, y++);
							cout << "Аккаунт " << person[0].login << " заблокирован." << endl;
							isCorrect = 1;
							_getch();
						}
								break;
						case '2': {
							vectInf[position].isActive = 1;
							GoToXY(x, y++);
							cout << "Аккаунт " << person[0].login << " рaзблокирован." << endl;
							isCorrect = 1;
							_getch();
						}
								break;
						}
					}
				}
				else {
					GoToXY(x, y++);
					cout << "Аккаунт " << person[0].login << " отсутствует" << endl;
					_getch();
					system("cls");
				}
				break;
		}
	}
}
bool AddContest() {
	infCont cont;
	bool isCorrect = 1;
	int x = 47;
	GoToXY(x, 11);
	cout << "ФИО конкурсанта: ";
	string a;
	a=getchar();
	getline(cin, cont.name);
	if (a != "\n")
		cont.name.insert(0, a);
	GoToXY(x, 12);
	cout << "Возраст конкурсанта: ";
	cin >> cont.year;
	if (cont.year <= 0 || cont.year > 20) {
		GoToXY(37, 14);
		cout << "Конкурсант не может быть старше 20 лет и " << endl;
		GoToXY(35, 15);
		cout << "его возраст не может быть меньше или равен ноль" << endl;
		GoToXY(47, 16);
		cout << "Конкурсант не добавлен." << endl;
		return 0;
	}
	GoToXY(x, 13);
	cout << "Страна конкурсанта: ";
	getchar();
	getline(cin, cont.country);
	GoToXY(x, 14);
	cout << "Музыкальный инструмент: ";
	getline(cin, cont.musicInst);
	do {
		GoToXY(x, 15);
		cout << "Занятое место: ";
		isCorrect = 1;
		cin >> cont.place;
		if (cont.place <= 0) {
			GoToXY(36, 17);
			cout << "Занятое место не может быть меньше или равно ноль." << endl;
			GoToXY(45, 18);
			cout << "Введите занятое место еще раз." << endl;
			_getch();
			system("cls");
			isCorrect = 0;
		}
	} while (isCorrect == 0);
	cont.rating = 0;
	vectCont.push_back(cont);
	system("cls");
	GoToXY(42, 11);
	cout << "Конкурсант успешно добавлен в систему." << endl << endl;
	return 1;
}

int Authorization(int& role) {
	fstream inf;

	inf.open("inf.txt", fstream::in);
	info person[2];
	person[0].role = role;
	GoToXY(50, 11);
	cout << "Введите логин: ";
	cin >> person[0].login;
	char ch;
	bool ctrlPressed = false;

	system("cls");
	GoToXY(51, 11);
	cout << "Введите пороль: ";
	person[0].password = "";

	while (true) {
		ch = _getch();
		if (ch == 13) { // 13 - код клавиши Enter
			break;
		}
		if (ch == 8 || ch == 127) { // 8 - код клавиши Backspace, 127 - код клавиши Delete
			if (person[0].password.length() > 0) {
				person[0].password.erase(person[0].password.length() - 1);
				cout << "\b \b"; // удаляем последнюю звездочку
			}
		}
		else if (ch >= 32 && ch <= 126 && ch != 0) { // игнорируем клавиши F1-F12
			if (ctrlPressed) { // проверяем, была ли нажата клавиша Ctrl
				if (ch == 'c' || ch == 'C' || ch == 'v' || ch == 'V') { // проверяем, была ли нажата клавиша C или V
					continue; // игнорируем клавиши сочетания
				}
			}
			person[0].password += ch;
			cout << '*';
		}
		else if (ch == -32) { // игнорируем коды направлений стрелок
			ch = _getch(); // считываем второй байт кода клавиши
			if (ch == 72 || ch == 75 || ch == 77 || ch == 80) { // проверяем, является ли второй байт кодом стрелки
				continue; // игнорируем стрелки
			}
		}
		else if (ch == 3 || ch == 22 || ch == 24) { // игнорируем клавиши сочетания Ctrl+C, Ctrl+V, Ctrl+X
			ctrlPressed = true;
		}
		else {
			ctrlPressed = false;
		}
	}
	bool isCorrect = 0;

	while (inf >> person[1].login) {
		inf >> person[1].password;
		inf >> person[1].role;
		inf >> person[1].isActive;
		if (person[0].login == person[1].login && person[0].password == person[1].password && person[0].role == person[1].role && person[1].isActive != 0)
			isCorrect = 1;
	}
	inf.close();

	if (isCorrect == 1)
		switch (role)
		{
		case 1: {
			system("cls");
			GoToXY(47, 11);
			cout << "Добро пожаловать в систему!" << endl;
			GoToXY(45, 12);
			cout << "Вы вошли от имени администратора." << endl;
			BackBlack();
			system("pause");
			role = 1;
		}
			  break;
		case 2: {
			system("cls");
			GoToXY(47, 11);
			cout << "Добро пожаловать в систему!" << endl;
			GoToXY(45, 12);
			cout << "Вы вошли от имени конкурсанта." << endl;
			BackBlack();
			system("pause");
			role = 2;
		}
			  break;
		case 3: {
			system("cls");
			GoToXY(47, 11);
			cout << "Добро пожаловать в систему!" << endl;
			GoToXY(45, 12);
			cout << "Вы вошли от имени пользователя." << endl;
			BackBlack();
			system("pause");
			role = 3;
		}
			  break;
			  return 0;
		}
	else {
		if (person[1].isActive == 0) {
			system("cls");
			GoToXY(50, 11);
			cout << "Данный аккаунт заблокирован." << endl;
			BackBlack();
			system("pause");
		}
		system("cls");
		GoToXY(50, 12);
		cout << "Авторизация не удалась." << endl;
		BackBlack();
		system("pause");
		return 0;
	}
}
void Registration(int& role, bool& isCorrect) {
	int numOfTimes = 0;
	info person[2];
	bool isCheck = 0;
	while (numOfTimes != 3) {
		GoToXY(48, 11);
		White();
		cout << "Введите имя пользователя: ";
		string ch; 
		ch = getchar();
		 getline(cin,person[0].login);
		 if (ch != "\n")
			 person[0].login.insert(0, ch);
		isCheck = 0;
		if (role == 3)
			person[0].role = role;
		else person[0].role = 2;

		for (int i = 0; i < vectInf.size() && isCheck == 0; i++) {
			if (vectInf[i].login == person[0].login)
				isCheck = 1;
		}
		if (isCheck == 1) {
			numOfTimes++;
			system("cls");
			White();
			GoToXY(48, 11);
			cout << "Введённое имя уже занято." << endl;
			GoToXY(46, 12);
			cout << "Оставшееся количество попыток: " << 3 - numOfTimes << endl << endl;
			_getch();
			system("cls");
		}
		else if (person[0].login.find(' ') != string::npos) {
			GoToXY(45, 12);
			cout << "Логин не должен содержать пробелов." << endl;
			_getch();
			system("cls");
		}
		else
			 {

			while (true) {
				char ch;
				bool ctrlPressed = false;

				//system("cls");

				for (int i = 0; i < 2; i++) {
					if (i == 0) {
						system("cls");
						GoToXY(51, 11);
						cout << "Введите пороль: ";
						person[i].password = "";
					}
					else {
						GoToXY(51, 12);
						cout << "Повторите пороль: ";
						person[i].password = "";
					}


					while (true) {
						ch = _getch();
						if (ch == 13) { // 13 - код клавиши Enter
							break;
						}
						if (ch == 8 || ch == 127) { // 8 - код клавиши Backspace, 127 - код клавиши Delete
							if (person[i].password.length() > 0) {
								person[i].password.erase(person[i].password.length() - 1);
								cout << "\b \b"; // удаляем последнюю звездочку
							}
						}
						else if (ch >= 32 && ch <= 126 && ch != 0) { // игнорируем клавиши F1-F12
							if (ctrlPressed) { // проверяем, была ли нажата клавиша Ctrl
								if (ch == 'c' || ch == 'C' || ch == 'v' || ch == 'V') { // проверяем, была ли нажата клавиша C или V
									continue; // игнорируем клавиши сочетания
								}
							}
							person[i].password += ch;
							cout << '*';
						}
						else if (ch == -32) { // игнорируем коды направлений стрелок
							ch = _getch(); // считываем второй байт кода клавиши
							if (ch == 72 || ch == 75 || ch == 77 || ch == 80) { // проверяем, является ли второй байт кодом стрелки
								continue; // игнорируем стрелки
							}
						}
						else if (ch == 3 || ch == 22 || ch == 24) { // игнорируем клавиши сочетания Ctrl+C, Ctrl+V, Ctrl+X
							ctrlPressed = true;
						}
						else {
							ctrlPressed = false;
						}
					}
				}

					 if (person[0].password != person[1].password) {
						GoToXY(51, 13);
						cout << "Пороли не совпадают." << endl;
						_getch();
						system("cls");
					} else if (person[0].password.size() < 8) {
						GoToXY(40, 12);
						cout << "Пароль должен содержать больше 8 символов." << endl;
						_getch();
						system("cls");
					}
					else if (person[0].password.find(' ') != string::npos) {
						 GoToXY(45, 12);
						 cout << "Пароль не должен содержать пробелов." << endl;
						 _getch();
						 system("cls");
					 }
					else break;
			}
			int a;
			

			if (role == 3) {
				a = 3;
				system("cls");
				GoToXY(49, 11);
				cout << "Регистрация прошла успешно." << endl;
				_getch();
				system("cls");
				isCorrect = 1;
			}
			else {
				a = 2;
				system("cls");
				GoToXY(44, 11);
				cout << "Пользователь успешно добавлен в систему." << endl;
				_getch();
				system("cls");
			}
			person[1].login = person[0].login;
			person[1].password = person[0].password;
			person[1].role = a;
			person[1].isActive = 1;
			vectInf.push_back(person[1]);
			numOfTimes = 3;
		}
	}
}

int OutCont() {
	int x=14, y=1;
	GoToXY(x,y++);
	cout << "=====================================================================================" << endl;
	GoToXY(x, y++);
	cout << "|ФИО                           |Возраст |Страна    |Инструмент     |Место |Рейтинг  |" << endl;
	GoToXY(x, y++);
	cout << "=====================================================================================" << endl;
	for (int i = 0; i < vectCont.size(); i++)
	{
		GoToXY(x, y++);
		cout << "|" << setw(30) << vectCont[i].name << "|" << setw(8) << vectCont[i].year
			<< "|" << setw(10) << vectCont[i].country << "|" << setw(15) << vectCont[i].musicInst
			<< "|" << setw(6) << vectCont[i].place << "|" << setw(9) << vectCont[i].rating << "|" << endl;
	}
	GoToXY(x, y++);
    cout << "=====================================================================================" << endl;
	return y;
}
void SetRating() {
	infCont cont;
	bool isCorrect = 0;
	int num; 
	system("cls");
	GoToXY(40, 11);
	cout << "Введите ФИО конкурсанта: ";
	string a;
	a = getchar();
	getline(cin, cont.name);
	if (a != "\n")
		cont.name.insert(0, a);

	for (int i = 0; i < vectCont.size() && isCorrect == 0; i++) 
		if (vectCont[i].name == cont.name) {
			isCorrect = 1;
			num = i;
		}
	if (isCorrect == 1) {
		bool isOK = 0;
		while (isOK == 0) {
			system("cls");
			GoToXY(50, 11);
			cout << "Введите рейтинг (1/10): ";
			cin >> cont.rating;
			if (cont.rating < 1 || cont.rating>10)
			{
				GoToXY(52, 13);
				cout << "Рейтинг введет неверно. " << endl;
				GoToXY(45, 14);
				cout << "Рейтинг не может быть ниже 1 и выше 10." << endl;
				_getch();
			}
			else {
				if (vectCont[num].rating == 0)
					vectCont[num].rating = cont.rating;
				else
				vectCont[num].rating = (vectCont[num].rating + cont.rating) / 2;
				system("cls");
				GoToXY(50, 11);
				cout << "Рейтинг выставлен." << endl;
				isOK = 1;
			}
		}
	}
	else {
		GoToXY(48, 12);
		cout << "Данный конкурсант не найден." << endl;
	}
}
void FindCont() {
	string cont_name;
	string a;
	GoToXY(55, 7);
	cout << "Поиск конкурсанта" << endl;
	GoToXY(50, 12);
	cout << "ФИО: ";
	getline(cin, a);
	if (a != "\n")
		cont_name = a;
	else getline(cin, cont_name);
	//if (a != "\n")
	//	cont_name.insert(0, a);
	system("cls");
	OutCont();
	GoToXY(38, 5);
	cout << "Информация о конкурсанте(ах) с ФИО: " << cont_name << endl;
	int x = 50, y = 7, count = 0;
	for (int i = 0; i < vectCont.size(); i++) {
		if (vectCont[i].name == cont_name) {
			count++;
			GoToXY(x - 3, y);
			cout << "№" << count;
			GoToXY(x, y++);
			cout << "ФИО: " << vectCont[i].name;
			GoToXY(x, y++);
			cout << "Возраст: " << vectCont[i].year;
			GoToXY(x, y++);
			cout << "Страна: " << vectCont[i].country;
			GoToXY(x, y++);
			cout << "Инструмент: " << vectCont[i].musicInst;
			GoToXY(x, y++);
			cout << "Место: " << vectCont[i].place;
			GoToXY(x, y++);
			cout << "Рейтинг: " << vectCont[i].rating;

			y++;
		}
	}
	if (count == 0) {
		GoToXY(48, 8);
		cout << "Данные о конкурсанте отсутствуют" << endl;
	}

}


//SORTING
void SortByAge() {
	for (int i = 0; i < vectCont.size(); i++) 
		for (int j = 0; j < vectCont.size()-1; j++) {
			if (vectCont[j].year > vectCont[i].year) 
				swap(vectCont[i], vectCont[j]);
		}

}
void SortByRating() {
	for (int i = 0; i < vectCont.size(); i++)
		for (int j = 0; j < vectCont.size() - 1; j++) {
			if (vectCont[j].rating < vectCont[i].rating) 
				swap(vectCont[i], vectCont[j]);
		}

}
void SortByInstrument(){
	for (int i = 0; i < vectCont.size(); i++)
		for (int j = 0; j < vectCont.size() - 1; j++) {
			if (vectCont[j].musicInst > vectCont[i].musicInst)
				swap(vectCont[i], vectCont[j]);
		}
}
void SortByName() {
	for (int i = 0; i < vectCont.size(); i++)
		for (int j = 0; j < vectCont.size() - 1; j++) {
			if (vectCont[j].name > vectCont[i].name)
				swap(vectCont[i], vectCont[j]);
		}
}
void SortByCountry() {
	for (int i = 0; i < vectCont.size(); i++)
		for (int j = 0; j < vectCont.size() - 1; j++) {
			if (vectCont[j].country > vectCont[i].country)
				swap(vectCont[i], vectCont[j]);
		}
}
void SortByPlace() {
	for (int i = 0; i < vectCont.size(); i++)
		for (int j = 0; j < vectCont.size() - 1; j++) {
			if (vectCont[j].place > vectCont[i].place)
				swap(vectCont[i], vectCont[j]);
		}
}


int Sort() {
	bool isCorrect = 0;
	string menu[] = { "Сортировать по возрасту", "Сортировать по рейтингу", "Сортировать по инструменту" , "Сортировать по имени" , "Сортировать по стране", "Сортировать по месту", "Назад"};
	int active_menu = 0;
	while (isCorrect == 0) {

		int x = 50, y = 10;
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu)
				BackAqua();
			else White();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		GoToXY(x, y++);

		char ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP: {
			if (active_menu > 0)
				--active_menu;
		}
			   break;
		case DOWN: {
			if (active_menu < size(menu) - 1)
				++active_menu;
		}
				 break;
		case ENTER:
			isCorrect = 1;
			switch (active_menu)
			{
			case 0:
				SortByAge();
				break;
			case 1: {
				SortByRating();
			}
				  break;
			case 2:
				SortByInstrument();
				break;
			case 3:
				SortByName();
				break;
			case 4:
				SortByCountry();
				break;
			case 5:
				SortByPlace();
				break;
			case 6: {
				White();
				system("cls");
				return 0;
			}
				  break;
			}
			break;
		}
	}
	system("cls");
}
void WinnersByAge() {
	SortByAge();
	int x = 14, y = 1;
	GoToXY(x, y++);
	cout << "=====================================================================================" << endl;
	GoToXY(x, y++);
	cout << "|ФИО                           |Возраст |Страна    |Инструмент     |Место |Рейтинг  |" << endl;
	GoToXY(x, y++);
	cout << "=====================================================================================" << endl;
	for (int i = 0; i < vectCont.size(); i++)
	{
		if (vectCont[i].place >= 1 && vectCont[i].place <= 3 && vectCont[i].year < 12) {
			GoToXY(x, y++);
			cout << "|" << setw(30) << vectCont[i].name << "|" << setw(8) << vectCont[i].year
				<< "|" << setw(10) << vectCont[i].country << "|" << setw(15) << vectCont[i].musicInst
				<< "|" << setw(6) << vectCont[i].place << "|" << setw(9) << vectCont[i].rating << "|" << endl;
			GoToXY(x, y++);
			cout << "=====================================================================================" << endl;
		}
	}
}
void WinnersByInst() {
	SortByInstrument();
	int num = 0;

	for (int i = 0; i < vectCont.size() - 2; i++) {
		for (int j = num; j < vectCont.size() && vectCont[j].musicInst == vectCont[j + 1].musicInst; j++) {
			if (vectCont[j].place >= vectCont[i].place) {
				infCont c = vectCont[i];
				vectCont[i] = vectCont[j];
				vectCont[j] = c;
			}
		}
		if (vectCont[i].musicInst != vectCont[i + 1].musicInst)
			num = i + 1;
	}

	int x = 14, y = 1;
	GoToXY(x, y++);
	cout << "================================================================" << endl;
	GoToXY(x, y++);
	cout << "|ФИО                           |Возраст |Инструмент     |Место |" << endl;
	GoToXY(x, y++);
	cout << "================================================================" << endl;
	for (int i = 0; i < vectCont.size(); i++) {
		if (vectCont[i].place >= 1 && vectCont[i].place <= 3) {
			GoToXY(x, y++);
			cout << "|" << setw(30) << vectCont[i].name << "|" << setw(8) << vectCont[i].year
				<< "|" << setw(15) << vectCont[i].musicInst
				<< "|" << setw(6) << vectCont[i].place << "|" << endl;
			GoToXY(x, y++);
			cout << "================================================================" << endl;
		}
	}
}
/////////////////////////////////////////////////

int list() {
	bool isCorrect = 0;
	string menu[] = { "Первые три места по классу инструментов", "Самые молодые победители конкурса", "Назад" };
	int active_menu = 0;
	while (isCorrect == 0) {

		int x = 50, y = 10;
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu)
				BackAqua();
			else White();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		GoToXY(x, y++);

		char ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP: {
			if (active_menu > 0)
				--active_menu;
		}
			   break;
		case DOWN: {
			if (active_menu < size(menu) - 1)
				++active_menu;
		}
				 break;
		case ENTER:
			switch (active_menu)
			{
			case 0:
				system("cls");
				WinnersByInst();
				_getch();
				system("cls");
				break;
			case 1: {
				system("cls");
				WinnersByAge();
				_getch();
				system("cls");
			}
				  break;
			case 2: {
				White();
				system("cls");
				return 0;
			}
			}
			break;
		}
	}
}


int ApplicationManagement() {
	if (vectApply.size() == 0) {
		GoToXY(55, 11);
		cout << "Заявления отсутствуют";
		_getch();
		return 0;
	}
	fstream newCont;
	bool isCorrect = 0, isOK = 0, isAccept = 0;
	string menu[] = { "Принять", "Отклонить" };
	int active_menu = 0;

	newCont.open("newContest.txt", fstream::app);
	for (int i = 0; i < vectApply.size() && isOK == 0; i++) {

		GoToXY(56, 5);
		cout << "ЗАЯВЛЕНИЕ №" << i+1 << endl;
		GoToXY(37, 6);
		Grey();
		cout << "(для остановки управлением заявками нажмите ESC)" << endl;
		White();
		int x = 50, y = 11;
		GoToXY(x, y++);
		cout << "ФИО: " << vectApply[i].name << endl;
		GoToXY(x, y++);
		cout << "Возраст: " << vectApply[i].year << endl;
		GoToXY(x, y++);
		cout << "Страна: " << vectApply[i].country << endl;
		GoToXY(x, y++);
		cout << "Музыкальный инструмент: " << vectApply[i].musicInst << endl;

		isAccept = 0;
		isCorrect = 0;
		while (isCorrect == 0) {
			x = 33, y = 20;
			for (int i = 0; i < size(menu); i++) {
				if (i == active_menu)
					BackAqua();
				else White();
				if (i == size(menu) - 1)
					GoToXY(x += 47, y);
				else GoToXY(x, y);
				cout << menu[i] << endl;
			}
			White();
			GoToXY(x, y++);

			char ch = _getch();
			if (ch == -32) ch = _getch();
			switch (ch)
			{
			case ESC: {
				isCorrect = 1;
				isOK = 1;
			}
					break;
			case LEFT: {
				if (active_menu > 0)
					--active_menu;
			}
					 break;
			case RIGHT: {
				if (active_menu < size(menu) - 1)
					++active_menu;
			}
					  break;
			case ENTER:
				switch (active_menu)
				{
				case 0:
					system("cls");
					GoToXY(55, 11);
					cout << "Заявление принято";
					isCorrect = 1;
					isAccept = 1;
					_getch();
					system("cls");
					break;
				case 1: {
					system("cls");
					GoToXY(55, 11);
					cout << "Заявление отклонено";
					isCorrect = 1;
					_getch();
					system("cls");
				}
					  break;
				}
				break;
			}
		}

		if (isAccept == 1)
			newCont << vectApply[i].year << endl << vectApply[i].name << endl << vectApply[i].country << endl << vectApply[i].musicInst << endl;
		vectApply.erase(vectApply.begin() + i);
		i--;
	}
	newCont.close();
}

//MENU
void menuAdmin(int& role) {
	bool isCorrect = 0;
	string menu[] = { "Зарегистрировать конкурсанта", "Добавить конкурсанта", "Управление учётными записями",
		"Вывести список участников", "Управлять заявками на участие",  "Сортировать конкурсантов" , "Поиск конкурсанта" , "Завершить работу программы"};
	int active_menu = 0;
	while (isCorrect == 0) {

		int x = 50, y = 10;
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu)
				BackAqua();
			else White();
			if (i == size(menu)-1)
				GoToXY(x, y += 2);
			else
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		GoToXY(x, y++);

		char ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP: {
			if (active_menu > 0)
				--active_menu;
		}
			   break;
		case DOWN: {
			if (active_menu < size(menu) - 1)
				++active_menu;
		}
				 break;
		case ENTER:
			switch (active_menu)
			{
			case 0:
				system("cls");
				Registration(role, isCorrect);
				system("cls");
				break;
			case 1: {
				system("cls");
				AddContest();
				_getch();
				system("cls");
			}
					break;
			case 2: {
				system("cls");
				ManagementAccount();
				system("cls");
			}
					break;
			case 3: {
				system("cls");
				OutCont();
				_getch();
				system("cls");
			}
					break;
			case 4: {
				system("cls");
				ApplicationManagement();
				system("cls");
			}
				  break;
			case 5: {
				system("cls");
				Sort();
			}
				  break;
			case 6: {
				system("cls");
				FindCont();
				_getch();
				system("cls");
			}
				  break;
			case 7: {
				BackBlack();
				system("cls");
				isCorrect = 1;
			}
				  break;
			}
			break;
		}
	}
}
bool menuAthor(int& role) {


	string choice_s;
	bool isCorrect = 0;
	if (role == 3) {
		string menu[] = { "Авторизироваться", "Регистрация", "Назад" };
		int active_menu = 0;
		while (isCorrect == 0) {

			int x = 50, y = 10;
			for (int i = 0; i < size(menu); i++) {
				if (i == active_menu)
					BackAqua();
				else White();
				GoToXY(x, y++);
				cout << menu[i] << endl;
			}
			GoToXY(x, y++);

			char ch = _getch();
			if (ch == -32) ch = _getch();
			switch (ch)
			{
			case UP: {
				if (active_menu > 0)
					--active_menu;
			}
				   break;
			case DOWN: {
				if (active_menu < size(menu) - 1)
					++active_menu;
			}
					 break;
			case ENTER:
				switch (active_menu)
				{
				case 0:
					system("cls");
					isCorrect = Authorization(role);
					_getch();
					system("cls");
					break;
				case 1: {
					system("cls");
					Registration(role, isCorrect);
					system("cls");
				}
					  break;
				case 2: {
					White();
					system("cls");
					return 0;
				}
				}
				break;
			}
		}
	}
	else {
		string menu[] = { "Авторизироваться", "Назад" };
		int active_menu = 0;
		while (isCorrect == 0) {

			int x = 50, y = 10;
			for (int i = 0; i < size(menu); i++) {
				if (i == active_menu)
					BackAqua();
				else White();
				GoToXY(x, y++);
				cout << menu[i] << endl;
			}
			GoToXY(x, y++);

			char ch = _getch();
			if (ch == -32) ch = _getch();
			switch (ch)
			{
			case ESC:
				exit(0);
				break;
			case UP: {
				if (active_menu > 0)
					--active_menu;
			}
				   break;
			case DOWN: {
				if (active_menu < size(menu) - 1)
					++active_menu;
			}
					 break;
			case ENTER:
				switch (active_menu)
				{
				case 0:
					system("cls");
					isCorrect = Authorization(role);
					system("cls");
					break;
				case 1: {
					White();
					system("cls");
					return 0;
				}
				}
				break;
			}
		}
	}
}
void menuUser(int& role) {

	string choice_s;
	bool isCorrect = 0;
	string menu[] = { "Вывести список участников", "Выставить рейтинг конкурсанту", "Сортировка конкурсантов" , "Поиск конкурсанта", 
		"Список по параметру" ,"Завершить работу программы"};
	int active_menu = 0;
	while (isCorrect == 0) {

		int x = 50, y = 10;
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu)
				BackAqua();
			else White();
			if (i == size(menu) - 1)
				GoToXY(x, y += 2);
			else
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		GoToXY(x, y++);

		char ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP: {
			if (active_menu > 0)
				--active_menu;
		}
			   break;
		case DOWN: {
			if (active_menu < size(menu) - 1)
				++active_menu;
		}
				 break;
		case ENTER:
			switch (active_menu)
			{
			case 0:
				system("cls");
				OutCont();
				_getch();
				system("cls");
				break;
			case 1: {
				system("cls");
				SetRating();
				_getch();
				system("cls");
			}
				  break;
			case 2:
				system("cls");
				Sort();
				break;

			case 3: {
				system("cls");
				FindCont();
				_getch();
				system("cls");
			}
				  break;
			case 4: {
				system("cls");
				list();
				system("cls");
			}
				  break;
			case 5: {
				BackBlack();
				system("cls");
				isCorrect = 1;
			}
				  break;
			}
			break;
		}
	}
}
void menuContest() {
	string choice_s;
	bool isCorrect = 0;
	string menu[] = { "Подать заявку на участие", "Вывести список участников", "Сортировка конкурсантов" , "Поиск конкурсанта" ,
		"Список по параметру" ,"Завершить работу программы"};
	int active_menu = 0;
	while (isCorrect == 0) {

		int x = 50, y = 10;
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu)
				BackAqua();
			else White();
			if (i == size(menu) - 1)
				GoToXY(x, y += 2);
			else
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		GoToXY(x, y++);

		char ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP: {
			if (active_menu > 0)
				--active_menu;
		}
			   break;
		case DOWN: {
			if (active_menu < size(menu) - 1)
				++active_menu;
		}
				 break;
		case ENTER:
			switch (active_menu)
			{
			case 0:
				system("cls");
				Apply();
				system("cls");
				break;
			case 1: {
				system("cls");
				OutCont();
				_getch();
				system("cls");	
			}
				  break;
			case 2: {
				system("cls");
				Sort();
			}
				  break;
			case 3: {
				system("cls");
				FindCont();
				_getch();
				system("cls");
			}
				  break;
			case 4: {
				system("cls");
				list();
				system("cls");
			}
				  break;
			case 5: {
				BackBlack();
				system("cls");
				isCorrect = 1;
			}
				  break;
			}
			break;
		}
	}
}
/////////////////////////////////////////////////



//OVERWRITING INFORMATION
void OverwriteInfo() {
	fstream inf;

	inf.open("inf.txt", fstream::out);
	for (int i = 0; i < vectInf.size(); i++) {
		if (i != 0)
			inf << endl;
		inf << vectInf[i].login << endl << vectInf[i].password 
			<< endl << vectInf[i].role << endl 
			<< vectInf[i].isActive;
	}
	inf.close();
}
void OverwriteCont() {
	fstream cont;

	cont.open("contest.txt", fstream::out);
	for (int i = 0; i < vectCont.size(); i++) {
		if (i != 0)
		cont << endl;
		cont << vectCont[i].year << endl << vectCont[i].name 
			<< endl << vectCont[i].country << endl 
			<< vectCont[i].musicInst<< endl << vectCont[i].place 
			<< endl << vectCont[i].rating;
	}
	cont.close();
}
void OverwriteApplyCont() {
	fstream apply;

	apply.open("statement.txt", fstream::out);
	for (int i = 0; i < vectApply.size(); i++) {
		if (i != 0)
			apply << endl;
		apply << vectApply[i].year << endl
			<< vectApply[i].name << endl
			<< vectApply[i].country << endl
			<< vectApply[i].musicInst;
	}
	apply.close();
}
/////////////////////////////////////////////////

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	SetConsoleTitle(L"Музыкальный конкурс");
	ConsoleCursorVisible(false, 100);



	readContest();
	ReadAppluCont();
	readInf();

	int role;
	string role_s;
	bool isCorrect = 0;
	int size_inf = 1;

	string choice_s;
	string menu[] = { "Администатор", "Конкурсант", "Пользователь",  "Завершить работу программы" };
	int active_menu = 0;
	

	while (isCorrect == 0) {
		White();
		GoToXY(34, 7);
		cout << " Добро пожаловать в музыкальное приложение " << endl;
		GoToXY(34, 8);
		cout << "         Пожалуйста, выберите роль         " << endl;

		int x = 50, y = 13;
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu)
				BackAqua();
			else White();
			GoToXY(x, y++);
			if(i == size(menu)-1)
				GoToXY(x-7, y++);
			cout << menu[i] << endl;
		}
		GoToXY(x, y++);

		char ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case ESC:
			exit(0);
			break;
		case UP: {
			if (active_menu > 0)
				--active_menu;
		}
			   break;
		case DOWN: {
			if (active_menu < size(menu) - 1)
				++active_menu;
		}
				 break;
		case ENTER:
			switch (active_menu)
			{
			case 0:
				role = 1;
				system("cls");
				if (menuAthor(role) == 0)
					break;
				else {
					system("cls");
					menuAdmin(role);
					isCorrect = 1;
					break;
				}
				break;
			case 1: {
				role = 2;
				system("cls");
				if (menuAthor(role) == 0)
					break;
				else {
					system("cls");
					menuContest();
					isCorrect = 1;
					break;
				}
			}
			case 2: {
				role = 3;
				system("cls");
				if (menuAthor(role) == 0)
					break;
				else {
					system("cls");
					menuUser(role);
					isCorrect = 1;
					break;
				}
			}
				  break;
			case 3: {
				BackBlack();
				system("cls");
				isCorrect = 1;
			}
			}
			break;
		}
	}

	White();
	GoToXY(50, 11);
	cout << "Работа программы завершена" << endl;
	BackAqua();
	GoToXY(38, 14);
	cout << "Спасибо, что воспользовались нашим приложением!" << endl;
	BackBlack();
	OverwriteInfo();
	OverwriteCont();
	OverwriteApplyCont();

}