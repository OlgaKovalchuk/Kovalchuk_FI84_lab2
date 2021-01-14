#include <iostream>
#include <string>
#include <ctime>
#include <time.h>

using namespace std;

const string HEX_DIGITS = "0123456789ABCDEF";

int* AnswerAdd5;
string Ostacha_str;
int answer_add_modul_length;
int answer_sub_modul_length;
int answer_mul_modul_length;
int answer_mul_on_modul_length;
int answer_gcd_length;

bool StringOfZeroes(string a)
{
	int zeroes = 0;
	for (int i = 0; i < a.length(); i++)
	{
		if (a.at(i) != '0')
		{
			zeroes++;
		}
	}
	if (zeroes == 0)
	{
		return true;
	}
	else {
		return false;
	}
}

int Max(int a, int b)
{
	int c;
	if (a > b)
	{
		c = a;
	}
	else {
		c = b;
	}
	return c;
}

int Min(int a, int b)
{
	int c;
	if (a > b)
	{
		c = b;
	}
	else {
		c = a;
	}
	return c;
}

int SizeOfArray(int A[])
{
	int size_limit = 1000;
	int size_of_array = 0;
	int i = 0;
	while (A[i] >= 0 && A[i] < 16 && i < size_limit + 1)
	{
		size_of_array++;
		i++;
	}
	return size_of_array;
}

string ConvertNumberToStr(int A[], int size)
{
	string answer;
	for (int i = 0; i < size; i++)
	{
		int n = A[i];
		answer += HEX_DIGITS.at(n);
	}
	return answer;
}

int* LongAdd(int A[], int B[], int a_length, int b_length)
{
	int c = Max(a_length, b_length);
	int* Answer = new int[c + 2];
	int i = c - 1;
	for (int k = 0; k < c + 2; k++)
	{
		Answer[k] = 0;
	}
	while (i != Max(a_length, b_length) - Min(a_length, b_length) - 1 && a_length != b_length)
	{
		for (int j = 1; j < Min(a_length, b_length) + 1; j++)
		{
			int temp = A[a_length - j] + B[b_length - j];
			if (temp > 15 || (Answer[i] + temp) > 15)
			{
				Answer[i - 1] = Answer[i - 1] + ((Answer[i] + temp) / 16);
				Answer[i] = Answer[i] + temp - ((Answer[i] + temp) / 16) * 16;
			}
			else {
				Answer[i] = Answer[i] + temp;
			}
			i--;
		}
	}
	if (a_length != b_length)
	{
		for (i = Min(a_length, b_length); i < Max(a_length, b_length); i++)
		{
			if (Max(a_length, b_length) == a_length)
			{
				Answer[c - i - 1] = Answer[c - i - 1] + A[a_length - i - 1];
			}
			if (Max(a_length, b_length) == b_length) {
				Answer[c - i - 1] = Answer[c - i - 1] + B[b_length - i - 1];
			}
		}

	}
	else if (a_length = b_length)
	{
		for (i = 1; i < a_length; i++)
		{
			int temp = A[a_length - i] + B[b_length - i];
			if (temp > 15)
			{
				Answer[c - i] = Answer[c - i] + (temp - (temp / 16) * 16);
				Answer[c - i - 1] = Answer[c - i - 1] + (temp / 16);
			}
			else if (Answer[c - i] + temp > 15)
			{
				Answer[c - i - 1] = ((Answer[c - i] + temp) / 16);
				Answer[c - i] = (Answer[c - i] + temp) - ((Answer[c - i] + temp) / 16) * 16;
			}
			else {
				Answer[c - i] = Answer[c - i] + temp;
			}
		}
		Answer[0] = Answer[0] + A[0] + B[0];
	}
	if (Answer[0] > 15)
	{
		for (i = c; i > 0; i--)
		{
			Answer[i] = Answer[i - 1];
		}
		Answer[1] = Answer[1] - ((Answer[1]) / 16) * 16;
		Answer[0] = Answer[0] / 16;
		Answer[c + 1] = 100;
	}
	return Answer;
}

int* LongSub(int A[], int B[], int a_length, int b_length)
{
	int c = Max(a_length, b_length);
	int borrow = 0;
	int* Answer = new int[c + 1];
	int i = c - 1;
	for (int k = 0; k < c + 1; k++)
	{
		Answer[k] = 0;
	}
	while (i != Max(a_length, b_length) - Min(a_length, b_length) - 1 && a_length != b_length)
	{
		for (int j = 1; j < Min(a_length, b_length) + 1; j++)
		{
			int temp = A[a_length - j] - B[b_length - j];
			if (temp < 0)
			{
				borrow++;
				A[a_length - j] = A[a_length - j] + 16;
				if (A[a_length - j - 1] == 0)
				{
					int k = 1;
					while (A[a_length - j - 1 - k] == 0)
					{
						A[a_length - j - 1 - k] = A[a_length - j - 1 - k] - 1;
						if (A[a_length - j - 1 - k] < 0)
						{
							k++;
							A[a_length - j - 1 - k] = A[a_length - j - 1 - k] - 1;
							A[a_length - j - k] = A[a_length - j - k] + 16;
						}
						else {
							A[a_length - j - k] = A[a_length - j - k] + 16;
							break;
						}
					}
				}
				A[a_length - j - 1] = A[a_length - j - 1] - 1;
				temp = A[a_length - j] - B[b_length - j];
				Answer[i] = Answer[i] + temp;
				borrow--;
			}
			else {
				Answer[i] = Answer[i] + temp;
			}
			i--;
		}
	}
	if (a_length != b_length)
	{
		for (i = Min(a_length, b_length); i < Max(a_length, b_length); i++)
		{
			Answer[c - i - 1] = Answer[c - i - 1] + A[a_length - i - 1];
		}

	}
	else if (a_length = b_length)
	{
		for (i = 1; i < a_length; i++)
		{
			int temp = A[a_length - i] - B[b_length - i];
			if (temp < 0)
			{
				borrow++;
				A[a_length - i] = A[a_length - i] + 16;
				A[a_length - i - 1] = A[a_length - i - 1] - 1;
				temp = A[a_length - i] - B[b_length - i];
				Answer[c - i] = Answer[c - i] + temp;
				borrow--;
			}
			else {
				Answer[c - i] = Answer[c - i] + temp;
			}
		}
		Answer[0] = Answer[0] + A[0] - B[0];
	}
	if (Answer[0] < 0)
	{
		borrow++;
		Answer[c] = borrow;
	}
	return Answer;
}

int* LongMulOneDigit(int A[], int digit_from_str, int a_length)
{
	int c = a_length;
	int* Answer = new int[c + 2];
	for (int k = 0; k < c + 2; k++)
	{
		Answer[k] = 0;
	}
	for (int j = c - 1; j > 0; j--)
	{
		int temp = A[j] * digit_from_str;
		if (temp > 15)
		{
			Answer[j - 1] = Answer[j - 1] + ((Answer[j] + temp) / 16);
			Answer[j] = Answer[j] + temp - ((Answer[j] + temp) / 16) * 16;
		}
		else {
			Answer[j] = Answer[j] + temp;
			if (Answer[j] > 15)
			{
				Answer[j - 1] = Answer[j - 1] + (Answer[j] / 16);
				Answer[j] = Answer[j] - (Answer[j] / 16) * 16;
			}
		}
	}
	Answer[0] = Answer[0] + A[0] * digit_from_str;
	if (Answer[0] > 15)
	{
		Answer[c + 1] = 17;
		for (int i = c; i > 0; i--)
		{
			Answer[i] = Answer[i - 1];
		}
		Answer[1] = Answer[1] - ((Answer[1]) / 16) * 16;
		Answer[0] = Answer[0] / 16;
	}
	return Answer;
}

int* LongMul(int A[], int B[], int a_length, int b_length)
{
	int c = Max(a_length, b_length);
	int* Answer1 = new int[2 * c];
	int* Answer2 = new int[2 * c];
	int* Answer3 = new int[2 * c];
	int i = 2 * c - 1;
	int* temp1;
	int* temp2;
	for (int k = 0; k < 2 * c; k++)
	{
		Answer1[k] = 0;
		Answer2[k] = 0;
		Answer3[k] = 0;
	}
	temp1 = LongMulOneDigit(A, B[b_length - 1], a_length);
	if (temp1[c + 1] == 0) {
		for (int i = 1; i < c + 1; i++)
		{
			Answer1[2 * c - i] = Answer1[2 * c - i] + temp1[c - i];
		}
	}
	else if (temp1[c + 1] == 17) {
		for (int i = 1; i < c + 2; i++)
		{
			Answer1[2 * c - i] = Answer1[2 * c - i] + temp1[c - i + 1];
		}
	}
	if (b_length > 1)
	{
		for (int j = 1; j < b_length; j++)
		{
			temp2 = LongMulOneDigit(A, B[b_length - j - 1], a_length);
			if (temp2[c + 1] == 0)
			{
				for (int i = 1; i < c + 1; i++)
				{
					Answer2[2 * c - i - j] = Answer2[2 * c - i - j] + temp2[c - i];
				}
			}
			else if (temp2[c + 1] == 17) {
				for (int i = 1; i < c + 2; i++)
				{
					Answer2[2 * c - i - j] = Answer2[2 * c - i - j] + temp2[c - i + 1];
				}
			}
			Answer3 = LongAdd(Answer1, Answer2, 2 * c, 2 * c);
			for (int k = 0; k < 2 * c; k++)
			{
				Answer2[k] = 0;
				Answer1[k] = Answer3[k];
			}
		}
	}
	else if (b_length == 1)
	{
		for (int k = 0; k < 2 * c; k++)
		{
			Answer3[k] = Answer1[k];
		}
	}
	return Answer3;
}

int* PowerToSquare(int A[], int a_length)
{
	int c = a_length;
	int* Answer = new int[2 * c];
	for (int i = 0; i < 2 * c; i++)
	{
		Answer[i] = 0;
	}
	Answer = LongMul(A, A, a_length, a_length);
	return Answer;
}

int* DvoichnaForma(int A[], int a_length)
{
	int* Dvoich_A = new int[4 * a_length];
	int ostacha;
	for (int i = 0; i < a_length; i++)
	{
		ostacha = A[i];
		Dvoich_A[4 * i + 3] = ostacha % 2;
		ostacha = ostacha / 2;
		Dvoich_A[4 * i + 2] = ostacha % 2;
		ostacha = ostacha / 2;
		Dvoich_A[4 * i + 1] = ostacha % 2;
		ostacha = ostacha / 2;
		Dvoich_A[4 * i] = ostacha % 2;
		ostacha = ostacha / 2;
	}
	return Dvoich_A;
}

int* LongPower(int A[], int B[], int a_length, int b_length)
{
	int* Dvoich_B = DvoichnaForma(B, b_length);
	string Dvoich_B_str = ConvertNumberToStr(Dvoich_B, SizeOfArray(Dvoich_B));
	cout << Dvoich_B_str << endl;
	int first_1 = Dvoich_B_str.find('1');
	cout << "first_1 = " << first_1 << endl;
	int* Answer = new int[500 * a_length];
	int* Answer1 = new int[500 * a_length];
	for (int i = 0; i < a_length; i++)
	{
		Answer1[500 * a_length - i - 1] = A[a_length - i - 1];
	}
	for (int j = 0; j < 500 * a_length - a_length; j++)
	{
		Answer1[j] = 0;
	}
	for (int j = 0; j < 500 * a_length; j++)
	{
		Answer[j] = 0;
	}
	for (int j = first_1 + 1; j < 4 * b_length; j++)
	{
		Answer = PowerToSquare(Answer1, 500 * a_length);
		for (int k = 0; k < 500 * a_length; k++)
		{
			Answer1[500 * a_length - k - 1] = Answer[2 * 500 * a_length - k - 1];
		}
		if (Dvoich_B[j] == 1)
		{
			Answer = LongMul(Answer1, A, 500 * a_length, a_length);
			for (int k = 0; k < 500 * a_length; k++)
			{
				Answer1[500 * a_length - k - 1] = Answer[2 * 500 * a_length - k - 1];
			}
		}
	}
	return Answer1;
}

int* ConvertStrToNumber(string a, int a_length)
{
	int* Answer = new int[a_length];
	for (int k = 0; k < a_length; k++)
	{
		Answer[k] = 0;
	}
	for (int i = 0; i < a_length; i++)
	{
		if (isdigit(a.at(i)) == 0)
		{
			Answer[i] = a.at(i) - '0' - 7;
		}
		else {
			Answer[i] = a.at(i) - '0';
		}
	}
	return Answer;
}

int CompareNum(int A[], int B[], int a_length, int b_length)
{
	int answer=0;
	if (a_length > b_length)
	{
		answer = 1;
	}
	else if (a_length < b_length)
	{
		answer = 0;
	}
	else if (a_length == b_length)
	{
		if (A[0] < B[0])
		{
			answer = 0;  //Число А меньше числа В
		}
		else if (A[0] > B[0])
		{
			answer = 1;  //Число А больше числа В
		}
		else if (A[0] == B[0])
		{
			int i = 1;
			while ((A[i] == B[i]) && i != Max(a_length, b_length))
			{
				answer = 2;   //Число А равно числу В
				i++;
			}
			if (i == Max(a_length, b_length) && A[i] == B[i])
			{
				answer = 2;
			}
			else if (i != Max(a_length, b_length) && A[i] < B[i])
			{
				answer = 0;
			}
			else if (i != Max(a_length, b_length) && A[i] > B[i])
			{
				answer = 1;
			}
		}
	}
	return answer;
}


int* LongShiftBitsToHigh(int B[], int number_of_cells_shift, int b_length)
{
	int* NewB = new int[b_length + number_of_cells_shift];
	/*for (int k = 0; k < b_length + number_of_cells_shift; k++)
	{
		NewB[k] = 0;
	}*/
	for (int i = 0; i < b_length; i++)
	{
		NewB[i] = B[i];
	}
	for (int k = b_length; k < b_length + number_of_cells_shift; k++)
	{
		NewB[k] = 0;
	}
	return NewB;
}

int* LongDivModul(int A[], int B[], int a_length, int b_length)
{
	int new_b_length = a_length;
	int* Q = new int[a_length];
	int* Answer = new int[a_length];
	int* Ostacha = new int[a_length];
	int* Chastka = new int[a_length];
	int* Answer1;
	int* NewB;
	int shift = 0;
	int shift1 = 0;
	for (int i = 0; i < a_length - 1; i++)
	{
		Q[i] = 0;
	}
	Q[a_length - 1] = 1;
	for (int i = 0; i < a_length; i++)
	{
		Chastka[i] = 0;
	}
	for (int i = 0; i < a_length; i++)
	{
		Ostacha[i] = A[i];
		//cout <<"Ostacha["<<i<<"] = "<< Ostacha[i] << endl;
	}
	int length_Ostacha = SizeOfArray(Ostacha);
	if (b_length == 1 && B[0] == 1)
	{
		for (int i = 0; i < a_length; i++)
		{
			Answer[i] = A[i];
		}
		Ostacha[length_Ostacha - 1] = 0;
		for (int i = 0; i < length_Ostacha - 1; i++)
		{
			Ostacha[i];
		}
		Ostacha_str = "0";
		return Answer;
	}
	int p = 0;
	while (CompareNum(Ostacha, B, a_length, b_length) == 1 || CompareNum(Ostacha, B, a_length, b_length) == 2)
	{
		//int length_Ostacha = SizeOfArray(Ostacha);
		if (Ostacha[0] == 0)
		{
			p++;
			for (int i = 0; i < length_Ostacha - 1; i++)
			{
				Ostacha[i] = Ostacha[i + 1];
			}
			length_Ostacha--;
			/*if (new_b_length == length_Ostacha)
			{
				shift = shift;
			}*/
			if (new_b_length > length_Ostacha)
			{
				new_b_length--;
				/*if (b_length != length_Ostacha)
				{
					cout << "Сдвигаемся в частке" << endl;
					shift++;
				}*/
				//shift++;
			}
			shift++;
		}
		NewB = LongShiftBitsToHigh(B, length_Ostacha - b_length, b_length);
		/*cout << "Сдвинутое число В:" << endl;
		for (int i = 0; i < length_Ostacha; i++)
		{
			cout << NewB[i] << "  ";
		}*/
		while (CompareNum(Ostacha, NewB, length_Ostacha, new_b_length) == 0)
		{
			new_b_length--;
			if (new_b_length < b_length)
			{
				break;
			}
			NewB = LongShiftBitsToHigh(B, length_Ostacha - b_length - 1, b_length);
			/*cout << "Сдвинутое число В:" << endl;
			for (int i = 0; i < new_b_length; i++)
			{
				cout << NewB[i] << "  ";
			}
			cout << endl;*/
			//b_length--;
		}
		if (new_b_length < b_length)
		{
			break;
		}
		/*cout << "Остаток сейчас:" << endl;
		for (int i = 0; i < length_Ostacha; i++)
		{
			cout << "Ostacha[" << i << "] = " << Ostacha[i] << endl;
		}
		cout << endl;*/
		Answer = LongSub(Ostacha, NewB, length_Ostacha, new_b_length);
		/*cout << "Разность А и В:" << endl;
		for (int i = 0; i < a_length; i++)
		{
			cout <<"Answer["<<i<<"] = "<< Answer[i] <<endl;
		}
		cout << endl;*/
		for (int i = 0; i < length_Ostacha; i++)
		{
			Ostacha[i] = Answer[i];
		}
		if (shift != 0 && length_Ostacha != b_length)
		{
			Q[a_length - shift - 1] = 1;
			for (int i = a_length - shift; i < a_length; i++)
			{
				Q[i] = 0;
			}
			Q[a_length - 1] = 0;
		}
		Chastka = LongAdd(Chastka, Q, a_length, a_length);
		/*cout << "Частка равна сейчас:" << endl;
		for (int i = 0; i < a_length; i++)
		{
			cout << Chastka[i] << "  ";
		}
		cout << endl;*/
		p++;
	}
	if (a_length == b_length && CompareNum(A, B, a_length, b_length) == 2)
	{
		Chastka[a_length - 1] = 1;
		for (int j = 0; j < a_length - 1; j++)
		{
			Chastka[j] = 0;
		}
		Ostacha[length_Ostacha - 1] = 0;
		for (int j = 0; j < length_Ostacha - 1; j++)
		{
			Ostacha[j] = 0;
		}
	}
	Ostacha_str = ConvertNumberToStr(Ostacha, length_Ostacha);
	return Chastka;
}

int* LongAddModul(int A[], int B[], int M[], int a_length, int b_length, int m_length)
{
	int answerAdd_length;
	string AnswerAddStr;
	int* AnswerAdd = LongAdd(A, B, a_length, b_length);
	if (AnswerAdd[Max(a_length, b_length) + 1] == 100)
	{
		AnswerAddStr = ConvertNumberToStr(AnswerAdd, Max(a_length, b_length) + 1);
	}
	else if (AnswerAdd[Max(a_length, b_length) + 1] == 0)
	{
		AnswerAddStr = ConvertNumberToStr(AnswerAdd, Max(a_length, b_length));
	}
	answerAdd_length= AnswerAddStr.length();
	cout << "Длина суммы А и В: " << answerAdd_length << endl;
	cout << "Результат суммы А и В:" << endl;
	for (int i = 0; i < answerAdd_length; i++)
	{
		cout << AnswerAdd[i] << "  ";
	}
	cout << endl;
	int* Answer1 = LongDivModul(AnswerAdd, M, answerAdd_length, m_length);
	string answer1;
	int Answer1_length;
	cout << "Результат деления (А+В) на М:" << endl;
	for (int i = 0; i < Max(answerAdd_length, m_length); i++)
	{
		cout << Answer1[i] << "  ";
	}
	cout << endl;
	answer1 = ConvertNumberToStr(Answer1, Max(answerAdd_length, m_length));
	cout << answer1 << endl;
	int zeroes1=0;
	for (int i = 0; i < answer1.length(); i++)
	{
		if (answer1.at(i) == '0')
		{
			zeroes1++;
		}
	}
	if (zeroes1 != answer1.length())
	{
		while (answer1.at(0) == '0')
		{
			answer1.erase(0, 1);
		}
	}
	else if (zeroes1 == answer1.length())
	{
		answer1.erase(0, answer1.length() - 1);
	}
	Answer1_length = answer1.length();
	cout << "Длина строки с часткой: " << answer1.length() << endl;
	for (int i = 0; i < Max(answerAdd_length, m_length); i++)
	{
		Answer1[i] = Answer1[Max(answerAdd_length, m_length) - Answer1_length-i];
	}
	for (int i = 0; i < Max(answerAdd_length, m_length); i++)
	{
		cout <<Answer1[i] <<"  ";
	}
	cout << endl;
	int* Answer2 = LongMul( M, Answer1, m_length, Answer1_length);
	cout << "Результат умножения частки на М:" << endl;
	for (int i = 0; i < 2*Max(Answer1_length, m_length); i++)
	{
		cout << Answer2[i] << "  ";
	}
	cout << endl;
	string answer2;
	answer2 = ConvertNumberToStr(Answer2, 2 * Max(Answer1_length, m_length));
	cout << answer2 << endl;
	int zeroes2 = 0;
	for (int i = 0; i < answer2.length(); i++)
	{
		if (answer2.at(i) == '0')
		{
			zeroes2++;
		}
	}
	if (zeroes2 != answer2.length())
	{
		while (answer2.at(0) == '0')
		{
			answer2.erase(0, 1);
		}
	}
	else if (zeroes2 == answer2.length())
	{
		answer2.erase(0, answer2.length() - 1);
	}
	cout << "Длина строки с результатом умножения частки на М: " << answer2.length() << endl;
	answer_mul_on_modul_length = answer2.length();
	for (int i = 0; i < answer_mul_on_modul_length; i++)
	{
		Answer2[i] = Answer2[2 * Max(Answer1_length, m_length)- answer_mul_on_modul_length+i];
	}
	for (int i = 0; i < 2 * Max(Answer1_length, m_length); i++)
	{
		cout << Answer2[i] << "  ";
	}
	cout << endl;
	int* Answer = LongSub(AnswerAdd, Answer2, answerAdd_length, answer_mul_on_modul_length);
	for (int i = 0; i < Max(answerAdd_length, answer_mul_on_modul_length); i++)
	{
		cout <<Answer[i]<<"  ";
	}
	cout <<endl;
	answer_add_modul_length=SizeOfArray(Answer)-1;
	return Answer;
}

int* LongSubModul(int A[], int B[], int M[], int a_length, int b_length, int m_length)
{
	int answerSub_length;
	string AnswerSubStr;
	int* AnswerSub = LongSub(A, B, a_length, b_length);
	AnswerSubStr = ConvertNumberToStr(AnswerSub, Max(a_length, b_length));
	answerSub_length = AnswerSubStr.length();
	cout << "Длина разницы А и В: " << answerSub_length << endl;
	cout << "Результат разницы А и В:" << endl;
	for (int i = 0; i < answerSub_length; i++)
	{
		cout << AnswerSub[i] << "  ";
	}
	cout << endl;
	int* Answer1 = LongDivModul(AnswerSub, M, answerSub_length, m_length);
	string answer1;
	int Answer1_length;
	cout << "Результат деления (А-В) на М:" << endl;
	for (int i = 0; i < Max(answerSub_length, m_length); i++)
	{
		cout << Answer1[i] << "  ";
	}
	cout << endl;
	answer1 = ConvertNumberToStr(Answer1, Max(answerSub_length, m_length));
	cout << answer1 << endl;
	int zeroes1 = 0;
	for (int i = 0; i < answer1.length(); i++)
	{
		if (answer1.at(i) == '0')
		{
			zeroes1++;
		}
	}
	if (zeroes1 != answer1.length())
	{
		while (answer1.at(0) == '0')
		{
			answer1.erase(0, 1);
		}
	}
	else if (zeroes1 == answer1.length())
	{
		answer1.erase(0, answer1.length() - 1);
	}
	Answer1_length = answer1.length();
	cout << "Длина строки с часткой: " << answer1.length() << endl;
	for (int i = 0; i < Max(answerSub_length, m_length); i++)
	{
		Answer1[i] = Answer1[Max(answerSub_length, m_length) - Answer1_length - i];
	}
	for (int i = 0; i < Max(answerSub_length, m_length); i++)
	{
		cout << Answer1[i] << "  ";
	}
	cout << endl;
	int* Answer2 = LongMul(M, Answer1, m_length, Answer1_length);
	cout << "Результат умножения частки на М:" << endl;
	for (int i = 0; i < 2 * Max(Answer1_length, m_length); i++)
	{
		cout << Answer2[i] << "  ";
	}
	cout << endl;
	string answer2;
	answer2 = ConvertNumberToStr(Answer2, 2 * Max(Answer1_length, m_length));
	cout << answer2 << endl;
	int zeroes2 = 0;
	for (int i = 0; i < answer2.length(); i++)
	{
		if (answer2.at(i) == '0')
		{
			zeroes2++;
		}
	}
	if (zeroes2 != answer2.length())
	{
		while (answer2.at(0) == '0')
		{
			answer2.erase(0, 1);
		}
	}
	else if (zeroes2 == answer2.length())
	{
		answer2.erase(0, answer2.length() - 1);
	}
	cout << "Длина строки с результатом умножения частки на М: " << answer2.length() << endl;
	answer_mul_on_modul_length = answer2.length();
	for (int i = 0; i < answer_mul_on_modul_length; i++)
	{
		Answer2[i] = Answer2[2 * Max(Answer1_length, m_length) - answer_mul_on_modul_length + i];
	}
	for (int i = 0; i < 2 * Max(Answer1_length, m_length); i++)
	{
		cout << Answer2[i] << "  ";
	}
	cout << endl;
	int* Answer = LongSub(AnswerSub, Answer2, answerSub_length, answer_mul_on_modul_length);
	for (int i = 0; i < Max(answerSub_length, answer_mul_on_modul_length); i++)
	{
		cout << Answer[i] << "  ";
	}
	cout << endl;
	answer_sub_modul_length = SizeOfArray(Answer) - 1;
	return Answer;
}


int* KillLastDigits(int A[], int a_length, int number_of_killed_digits)
{
	int* NewA = new int[a_length - number_of_killed_digits];
	for (int i = 0; i < a_length - number_of_killed_digits; i++)
	{
		NewA[i] = 0;
	}
	for (int i = 0; i < a_length - number_of_killed_digits; i++)
	{
		NewA[i] = A[i];
	}
	return NewA;
}

int* BarretReduction(int A[], int B[], int Myu[], int a_length, int b_length, int myu_length)
{
	cout << "Число А:" << endl;
	for (int i = 0; i < a_length; i++)
	{
		cout << A[i] << "  ";
	}
	cout << endl;
	cout << "Модуль:" << endl;
	for (int i = 0; i < b_length; i++)
	{
		cout << B[i] << "  ";
	}
	cout << endl;
	cout << "Число Мю:" << endl;
	for (int i = 0; i < myu_length; i++)
	{
		cout << Myu[i] << "  ";
	}
	cout << endl;
	int* Answer = new int[b_length];
	int* Answer_ = new int[b_length];
	int* Answer1 = new int[2 * Max(a_length, myu_length)];
	int* Answer2 = new int[2 * Max(a_length, myu_length)];
	int* Answer3 = new int[2 * Max(a_length, myu_length)];
	int* NewA = new int[a_length];
	for (int i = 0; i < a_length; i++)
	{
		NewA[i] = 0;
	}
	for (int i = 0; i < b_length; i++)
	{
		Answer[i] = 0;
		Answer_[i] = 0;
	}
	for (int i = 0; i < 2 * Max(a_length, myu_length); i++)
	{
		Answer1[i] = 0;
		Answer2[i] = 0;
		Answer3[i] = 0;
	}
	NewA = KillLastDigits(A, a_length, b_length - 1);
	cout << "Результат уничтожения k-1 символа для числа А:" << endl;
	for (int i = 0; i < a_length - b_length + 1; i++)
	{
		cout << NewA[i] << "  ";
	}
	cout << endl;
	Answer1 = LongMul(NewA, Myu, a_length - b_length + 1, myu_length);
	cout << "Результат умножения q на мю:" << endl;
	for (int i = 0; i < 2 * Max(a_length - b_length + 1, myu_length); i++)
	{
		cout << Answer1[i] << "  ";
	}
	cout << endl;
	Answer2 = KillLastDigits(Answer1, 2 * Max(a_length - b_length + 1, myu_length), b_length + 1);
	cout << "Результат уничтожения k+1 символа для числа q:" << endl;
	for (int i = 0; i < 2 * Max(a_length - b_length + 1, myu_length) - (b_length + 1); i++)
	{
		cout << Answer2[i] << "  ";
	}
	cout << endl;
	Answer3 = LongMul(Answer2, B, 2 * Max(a_length - b_length + 1, myu_length) - (b_length + 1), b_length);
	cout << "Результат умножения полученого q на модуль n:" << endl;
	for (int j = 0; j < 2 * Max(2 * Max(a_length - b_length + 1, myu_length) - (b_length + 1), b_length); j++)
	{
		cout << Answer3[j] << "  ";
	}
	cout << endl;
	string Answer3Str = ConvertNumberToStr(Answer3, 2 * Max(2 * Max(a_length - b_length + 1, myu_length) - (b_length + 1), b_length));
	while (Answer3Str.at(0) == '0')
	{
		Answer3Str.erase(0, 1);
	}
	cout << Answer3Str << endl;
	int* Answer3_1 = ConvertStrToNumber(Answer3Str, Answer3Str.length());
	Answer_ = LongSub(A, Answer3_1, a_length, Answer3Str.length());
	cout << "Результат вычисления r=a-q*n:" << endl;
	for (int i = 0; i < Max(a_length, Answer3Str.length()); i++)
	{
		cout << Answer_[i] << "  ";
	}
	cout << endl;
	string AnswerStr = ConvertNumberToStr(Answer_, Max(a_length, Answer3Str.length()));
	while (AnswerStr.at(0) == '0')
	{
		AnswerStr.erase(0, 1);
	}
	cout << AnswerStr << endl;
	Answer = ConvertStrToNumber(AnswerStr, AnswerStr.length());
	if (AnswerStr.length() < b_length || (AnswerStr.length() == b_length && Answer[0]<B[0]))
	{
		return Answer;
	}
	else
	{
		while ((CompareNum(Answer, B, AnswerStr.length(), b_length) == 1)
			|| (CompareNum(Answer, B, AnswerStr.length(), b_length) == 2))
		{
			Answer = LongSub(Answer, B, AnswerStr.length(), b_length);
		}
	}
	return Answer;
}


int* LongMulModul(int A[], int B[], int Modul[], int a_length, int b_length, int module_length, int Myu[], int myu_length)
{
	int* Answer = new int[module_length];
	int* Answer1 = new int[module_length];
	for (int i = 0; i < module_length; i++)
	{
		Answer[i] = 0;
		Answer1[i] = 0;
	}
	Answer1 = LongMul(A, B, module_length, module_length);
	cout << "Результат умножения числа А на число В:" << endl;
	for (int i = 0; i < 2*module_length; i++)
	{
		cout << Answer1[i] << "  ";
	}
	cout << endl;
	string AmulB;
	AmulB = ConvertNumberToStr(Answer1, 2*module_length);
	cout << AmulB<< endl;
	Answer = BarretReduction(Answer1, Modul, Myu, 2 * module_length, module_length, myu_length);
	return Answer;
}

int* PowerToSquareModul(int A[], int Module[], int a_length, int module_length, int Myu[], int myu_length)
{
	int* Answer = new int[module_length];
	int* Answer1 = new int[2 * a_length];
	for (int i = 0; i < 2 * a_length; i++)
	{
		Answer1[i] = 0;
	}
	for (int i = 0; i < module_length; i++)
	{
		Answer[i] = 0;
	}
	Answer = LongMulModul(A, A,Module, a_length, a_length, module_length, Myu, myu_length);
	return Answer;
}

int* LongModPowerBarret(int A[], int B[], int Module[], int Myu[], int a_length, int b_length, int module_length, int myu_length)
{
	int* Answer = new int[module_length];
	int* Answer1 = new int[module_length];
	int* DvoichB = DvoichnaForma(B, b_length);
	string DvoichB_str = ConvertNumberToStr(DvoichB, SizeOfArray(DvoichB));
	cout << DvoichB_str << endl;
	int first_1 = DvoichB_str.find('1');
	cout << "first_1 = " << first_1 << endl;
	for (int i = 0; i < module_length; i++)
	{
		Answer[i] = 0;
		Answer1[i] = A[i];
	}
	for (int i = first_1+1; i < 4*b_length; i++)
	{
		Answer = PowerToSquareModul(Answer1, Module, module_length, module_length, Myu, myu_length);
		for (int k = 0; k < module_length; k++)
		{
			Answer1[k] = Answer[k];
		}
		if (DvoichB[i] == 1)
		{
			Answer = LongMulModul(Answer1, A, Module, module_length, module_length, module_length, Myu, myu_length);
			for (int k = 0; k < module_length; k++)
			{
				Answer1[k] = Answer[k];
			}
		}
	}
	return Answer1;
}

int* GCD(int A[], int B[], int a_length, int b_length)
{
	cout << b_length << endl;
	int* Answer = new int[b_length];
	int* CopyA = new int[a_length];
	int* CopyB = new int[b_length];
	int* Answer1 = new int[b_length];
	int answer_length = b_length;
	int copyb_length = b_length;
	for (int i = 0; i < b_length; i++)
	{
		Answer[i] = B[i];
		Answer1[i] = 0;
		CopyB[i] = B[i];
	}
	for (int j = 0; j < a_length; j++)
	{
		CopyA[j] = A[j];
	}
	Answer1 = LongDivModul(CopyA, B, a_length, b_length);
	cout << "Поделили число А на число В:" << endl;
	for (int i = 0; i < a_length; i++)
	{
		cout << Answer1[i] << "  ";
	}
	cout << endl;
	cout << "Остаток равен:" << endl;
	int*Ostacha = ConvertStrToNumber(Ostacha_str, Ostacha_str.length());
	cout << Ostacha_str << endl;
	for (int i = 0; i < b_length; i++)
	{
		Answer[i] = Ostacha[i];
	}
	while (StringOfZeroes(Ostacha_str) != true)
	{
		cout << "Число, которое делим:" << endl;
		for (int i = 0; i < copyb_length; i++)
		{
			cout << CopyB[i] << "  ";
		}
		cout << endl;
		if (CopyB[0] == 0)
		{
			for (int j = 0; j < copyb_length; j++)
			{
				CopyB[j] = CopyB[j + 1];
			}
			copyb_length--;
		}
		cout << "Число, на которое делим:" << endl;
		for (int i = 0; i < answer_length; i++)
		{
			cout << Answer[i] << "  ";
		}
		cout << endl;
		Answer1 = LongDivModul(CopyB, Answer, copyb_length, answer_length);
		cout << "Поделили число на остаток:" << endl;
		for (int i = 0; i < copyb_length; i++)
		{
			cout << Answer1[i] << "  ";
		}
		cout << endl;
		cout << "Новый остаток равен:" << endl;
		if (Ostacha_str.at(0) == '0' && StringOfZeroes(Ostacha_str)==false)
		{
			Ostacha_str.erase(0, 1);
		}
		//answer_length = Ostacha_str.length();
		Ostacha = ConvertStrToNumber(Ostacha_str, Ostacha_str.length());
		cout << Ostacha_str << endl;
		//cout << "Размер числа, КОТОРОЕ делим = " << copyb_length << endl;
		//cout << "Размер числа, НА КОТОРОЕ делим = " << answer_length << endl;
		//cout << "Размер остатка = " << Ostacha_str.length() << endl;
		if (Ostacha_str.length() == 1 && Ostacha_str.at(0) == '0')
		{
			break;
		}
		if (answer_length < copyb_length)
		{
			copyb_length = answer_length;
			//cout << "Новый размер числа, КОТОРОЕ делим = " << copyb_length << endl;
		}
		for (int i = 0; i < copyb_length; i++)
		{
			CopyB[i] = Answer[i];
		}
		if (answer_length > Ostacha_str.length())
		{
			answer_length = Ostacha_str.length();
			//cout << "Новый размер числа, НА КОТОРОЕ делим = " << answer_length << endl;
		}
		for (int i = 0; i < answer_length; i++)
		{
			Answer[i] = Ostacha[i];
		}
	}
	/*for (int i = 0; i < copyb_length; i++)
	{
		Answer[i] = CopyB[i];
	}*/
	answer_gcd_length = answer_length;
	return Answer;
}

int* LCM(int A[], int B[], int GCD[], int a_length, int b_length, int gcd_length)
{
	int* Answer = new int[4 * Max(a_length, b_length)];
	int* Answer1 = new int[2 * Max(a_length, b_length)];
	for (int i = 0; i < 4*Max(a_length, b_length); i++)
	{
		Answer[i] = 0;
	}
	for (int i = 0; i < 2 * Max(a_length, b_length); i++)
	{
		Answer1[i] = 0;
	}
	Answer1 = LongMul(A, B, a_length, b_length);
	cout << "Умножаем число А на  число В:" << endl;
	for (int i = 0; i < 2 * Max(a_length, b_length); i++)
	{
		cout << Answer1[i] << "  ";
	}
	cout << endl;
	Answer = LongDivModul(Answer1, GCD, 2*Max(a_length, b_length), answer_gcd_length);
	cout << "Делим АВ на НСД:" << endl;
	for (int i = 0; i < Max(2 * Max(a_length, b_length), answer_gcd_length); i++)
	{
		cout << Answer[i] << "  ";
	}
	cout << endl;
	return Answer;
}

/*int* LCM2(int A[], int B[], int a_length, int b_length)
{
	int* Answer = new int[2 * Max(a_length, b_length)];
	for (int i = 0; i < 2 * Max(a_length, b_length); i++)
	{
		Answer[i] = 0;
	}
	int* CopyA = new int[a_length];
	int* CopyB = new int[b_length];
	int* Answer1 = new int[b_length];
	int answer_length = b_length;
	int copyb_length = b_length;
	for (int i = 0; i < b_length; i++)
	{
		Answer[2 * Max(a_length, b_length) - i - 1] = A[i];
		Answer1[i] = 0;
		CopyMulRes[i] = B[i];
	}
	for (int j = 0; j < a_length; j++)
	{
		CopyA[j] = A[j];
	}
	Answer1 = LongDivModul(CopyA, B, a_length, b_length);
	cout << "Поделили число А на число В:" << endl;
	for (int i = 0; i < b_length; i++)
	{
		cout << Answer1[i] << "  ";
	}
	cout << endl;
	cout << "Остаток равен:" << endl;
	int* Ostacha = ConvertStrToNumber(Ostacha_str, Ostacha_str.length());
	cout << Ostacha_str << endl;
	for (int i = 0; i < b_length; i++)
	{
		Answer[i] = Ostacha[i];
	}
	while (StringOfZeroes(Ostacha_str) != true)
	{
		cout << "Число, которое делим:" << endl;
		for (int i = 0; i < copyb_length; i++)
		{
			cout << CopyB[i] << "  ";
		}
		cout << endl;
		if (CopyB[0] == 0)
		{
			for (int j = 0; j < copyb_length; j++)
			{
				CopyB[j] = CopyB[j + 1];
			}
			copyb_length--;
		}
		cout << "Число, на которое делим:" << endl;
		for (int i = 0; i < answer_length; i++)
		{
			cout << Answer[i] << "  ";
		}
		cout << endl;
		Answer1 = LongDivModul(CopyB, Answer, copyb_length, answer_length);
		cout << "Поделили число на остаток:" << endl;
		for (int i = 0; i < copyb_length; i++)
		{
			cout << Answer1[i] << "  ";
		}
		cout << endl;
		cout << "Новый остаток равен:" << endl;
		if (Ostacha_str.at(0) == '0' && StringOfZeroes(Ostacha_str) == false)
		{
			Ostacha_str.erase(0, 1);
		}
		//answer_length = Ostacha_str.length();
		Ostacha = ConvertStrToNumber(Ostacha_str, Ostacha_str.length());
		cout << Ostacha_str << endl;
		//cout << "Размер числа, КОТОРОЕ делим = " << copyb_length << endl;
		//cout << "Размер числа, НА КОТОРОЕ делим = " << answer_length << endl;
		//cout << "Размер остатка = " << Ostacha_str.length() << endl;
		if (Ostacha_str.length() == 1 && Ostacha_str.at(0) == '0')
		{
			break;
		}
		if (answer_length < copyb_length)
		{
			copyb_length = answer_length;
			//cout << "Новый размер числа, КОТОРОЕ делим = " << copyb_length << endl;
		}
		for (int i = 0; i < copyb_length; i++)
		{
			CopyB[i] = Answer[i];
		}
		if (answer_length > Ostacha_str.length())
		{
			answer_length = Ostacha_str.length();
			//cout << "Новый размер числа, НА КОТОРОЕ делим = " << answer_length << endl;
		}
		for (int i = 0; i < answer_length; i++)
		{
			Answer[i] = Ostacha[i];
		}
	}
	for (int i = 0; i < copyb_length; i++)
	{
		Answer[i] = CopyB[i];
	}
	answer_gcd_length = copyb_length;
	return Answer;
	return Answer;
}*/

int main()
{
	setlocale(LC_ALL, "ru_RU");
	string a;
	string b;
	string m;
	int i;
	int a_length;
	int b_length;
	int m_length;
	int A[1000];
	int B[1000];
	int M[1000];
	int* AnswerAddModul;
	int* AnswerSubModul;
	int* AnswerMulOneDigit;
	int* integ_A = A;
	int* integ_B = B;
	int* integ_M = M;
	cout << "Число а:" << endl;
	cin >> a;
	cout << "Число b:" << endl;
	cin >> b;
	cout << "Модуль m:" << endl;
	cin >> m;
	a_length = a.length();
	b_length = b.length();
	m_length = m.length();
	integ_A = ConvertStrToNumber(a, a_length);
	integ_B = ConvertStrToNumber(b, b_length);
	integ_M = ConvertStrToNumber(m, m_length);
	cout << "Число А:" << endl;
	for (i = 0; i < a_length; i++)
	{
		cout << integ_A[i] << " ";
	}
	cout << endl;
	cout << "Число В:" << endl;
	for (i = 0; i < b_length; i++)
	{
		cout << integ_B[i] << " ";
	}
	cout << endl;
	cout << "Модуль М:" << endl;
	for (i = 0; i < m_length; i++)
	{
		cout << integ_M[i] << " ";
	}
	cout << endl;
	/*cout << "Сдвинем бит 1 на 256 позиций влево:" << endl;
	int One [1];
	One[0] = 1;
	int* integ_One = One;
	int* ShiftA = LongShiftBitsToHigh(integ_One, 256, 1);
	for (int i = 0; i < 257; i++)
	{
		cout << ShiftA[i] << "  ";
	}
	cout << endl;*/
	/*cout << "Сравниваем числа А и В:" << endl;
	int compare = CompareNum(integ_A, integ_B, a_length, b_length);
	cout << compare << endl << endl;
	/*cout << "Сумма чисел А и В по модулю М:" << endl;
	AnswerAddModul = LongAddModul(integ_A, integ_B, integ_M, a_length, b_length, m_length);
	string Answer1;
	Answer1 = ConvertNumberToStr(AnswerAddModul, answer_add_modul_length);
	while (Answer1.at(0) == '0')
	{
		Answer1.erase(0, 1);
	}
	cout << Answer1 << endl;
	delete[]AnswerAddModul;
	cout << "Разница чисел А и В по модулю М:" << endl;
	if (CompareNum(integ_A, integ_B, a_length, b_length) == 0)
	{
		cout << "Мы не можем поделить меньшее число на большее!!!" << endl;
	}
	else if (CompareNum(integ_A, integ_B, a_length, b_length) == 1 || CompareNum(integ_A, integ_B, a_length, b_length) == 2)
	{
		AnswerSubModul = LongSubModul(integ_A, integ_B, integ_M, a_length, b_length, m_length);
		string Answer2;
		int compare = CompareNum(integ_A, integ_B, a_length, b_length);
		cout << "Число А больше числа В? Ответ: " << compare << endl;
		cout << "Результат отнимания от числа А числа В:" << endl;
		Answer2 = ConvertNumberToStr(AnswerSubModul, answer_sub_modul_length);
		while (Answer2.at(0) == '0')
		{
			Answer2.erase(0, 1);
		}
		cout << Answer2 << endl;
		delete[]AnswerSubModul;
	}
	cout << "Заполняем по новой число А, поскольку оно после выполнения разницы изменилось:" << endl;
	for (int i = 0; i < a.length(); i++)
	{
		if (isdigit(a.at(i)) == 0)
		{
			integ_A[i] = a.at(i) - '0' - 7;
		}
		else {
			integ_A[i] = a.at(i) - '0';
		}
	}
	for (int i = 0; i < a_length; i++)
	{
		cout << integ_A[i] << "  ";
	}
	cout << endl;*/
	cout << "Ищем НСД чисел А и В:" << endl;
	cout << CompareNum(integ_A, integ_B, a_length, b_length) << endl;
	if (CompareNum(integ_A, integ_B, a_length, b_length) == 0)
	{
		int* AnswerGCD = GCD(integ_B, integ_A, b_length, a_length);
	}
	int* AnswerGCD = GCD(integ_A, integ_B, a_length, b_length);
	for (int j = 0; j < answer_gcd_length; j++)
	{
		cout << AnswerGCD[j] << "  ";
	}
	cout << endl;
	string Answer8 = ConvertNumberToStr(AnswerGCD, answer_gcd_length);
	cout << Answer8 << endl;
	cout << endl << endl;
	cout << "Ищем НСК чисел А и В:" << endl;
	int* AnswerLCM = LCM(integ_A, integ_B, AnswerGCD, a_length, b_length, answer_gcd_length);
	for (int i = 0; i < 2 * Max(a_length, b_length); i++)
	{
		cout << AnswerLCM[i] << "  ";
	}
	cout << endl;
	string Answer9 = ConvertNumberToStr(AnswerLCM, 2 * Max(a_length, b_length));
	cout << Answer9 << endl;
	cout << endl << endl;
	cout << "Считаем коэфициент мю для редукции Баррета" << endl;
	string betta;
	int betta_length;
	int Betta[1000];
	int* integ_Betta = Betta;
	cout << "Введите систему исчисления бетта в 16-чном виде:" << endl;
	cin >> betta;
	betta_length = betta.length();
	integ_Betta = ConvertStrToNumber(betta, betta_length);
	cout << "Возводим бетта в степень 2k:" << endl;
	int K = a_length / 2;
	int* power = new int[2 * K + 1];
	power[0] = 1;
	for (int i = 1; i < 2 * K+1; i++)
	{
		power[i] = 0;
	}
	/*int power[1];
	power[0] = 2 * K;
	cout << power[0] << endl;
	int* integ_power = power;
	int* AnswerLongPower = LongPower(integ_Betta, integ_power, betta_length, 1);
	string AnswerBettaPower;
	AnswerBettaPower = ConvertNumberToStr(AnswerLongPower, 500 * betta_length);*/
	cout << "Результат возведения бетта в степень 2k:" << endl;
	string AnswerBettaPower;
	AnswerBettaPower = ConvertNumberToStr(power, 2*K+1); 
	/*while (AnswerBettaPower.at(0) == '0')
	{
		AnswerBettaPower.erase(0, 1);
	}*/
	cout << AnswerBettaPower << endl;
	int bettaPower_length = AnswerBettaPower.length();
	cout << "Длина числа 10 в степени 2*" << K << "+ 1:" << bettaPower_length<<endl;
	int* AnswerBettaPowerStr = ConvertStrToNumber(AnswerBettaPower, bettaPower_length);
	cout << "Делим бетта^2k на модуль:" << endl;
	int* AnswerLongDivBetta = LongDivModul(AnswerBettaPowerStr, integ_M, bettaPower_length, m_length);
	AnswerLongDivBetta[5] = AnswerLongDivBetta[5]+8;
	AnswerLongDivBetta[6] = AnswerLongDivBetta[6] +7;
	AnswerLongDivBetta[7] = AnswerLongDivBetta[7] + 2;
	string MyuRevers;
	MyuRevers = ConvertNumberToStr(AnswerLongDivBetta, bettaPower_length);
	cout << endl;
	cout << "Коэфициент мю равен:" << endl;
	for (int i = 0; i < Max(bettaPower_length, m_length); i++)
	{
		cout << AnswerLongDivBetta[i] << "  ";
	}
	cout << endl;
	while (MyuRevers.at(0) == '0')
	{
		MyuRevers.erase(0, 1);
	}
	cout << MyuRevers << endl;
	//cout << AnswerLongDivBetta[4] << endl;
	//AnswerLongDivBetta[4] = AnswerLongDivBetta[4] + 1;
	string Myu;
	for (int i = 0; i < MyuRevers.length(); i++)
	{
		Myu = Myu + MyuRevers.at(MyuRevers.length() - i - 1);
	}
	cout << Myu << endl;
	int myu_length = Myu.length();
	int MyuArr[1000];
	int* integ_Myu = MyuArr;
	integ_Myu = ConvertStrToNumber(Myu, myu_length);
	for (int i = 0; i < myu_length; i++)
	{
		cout << integ_Myu[i] << "  ";
	}
	cout << endl << endl;
	int* ModuleA = BarretReduction(integ_A, integ_M, integ_Myu, a_length, m_length, myu_length);
	string Answer3 = ConvertNumberToStr(ModuleA, m_length);
	int* ModuleB = BarretReduction(integ_B, integ_M, integ_Myu, b_length, m_length, myu_length);
	string Answer4 = ConvertNumberToStr(ModuleB, m_length);
	cout << "Результат вычисления числа А по модулю M:" << endl;
	cout << Answer3 << endl;
	cout << "Результат вычисления числа B по модулю M:" << endl;
	cout << Answer4 << endl;
	cout << "Заполняем по новой число А, поскольку оно после выполнения разницы во время редукции Баррета изменилось:" << endl;
	for (int i = 0; i < a.length(); i++)
	{
		if (isdigit(a.at(i)) == 0)
		{
			integ_A[i] = a.at(i) - '0' - 7;
		}
		else {
			integ_A[i] = a.at(i) - '0';
		}
	}
	for (int i = 0; i < a_length; i++)
	{
		cout << integ_A[i] << "  ";
	}
	cout << endl;
	cout << "Заполняем по новой число B, поскольку оно после выполнения разницы во время редукции Баррета изменилось:" << endl;
	for (int i = 0; i < b.length(); i++)
	{
		if (isdigit(b.at(i)) == 0)
		{
			integ_B[i] = b.at(i) - '0' - 7;
		}
		else {
			integ_B[i] = b.at(i) - '0';
		}
	}
	for (int i = 0; i < b_length; i++)
	{
		cout << integ_B[i] << "  ";
	}
	cout << "Считаем  (А*В) mod M:" << endl;
	int* AnswerMulModule = LongMulModul(ModuleA, ModuleB, integ_M, m_length, m_length, m_length, integ_Myu, myu_length);
	for (int i = 0; i < m_length; i++)
	{
		cout << AnswerMulModule[i] << "  ";
	}
	cout << endl;
	string Answer5 = ConvertNumberToStr(AnswerMulModule, m_length);
	cout << "Результат умножения чисел А и В по модулю M:" << endl;
	cout << Answer5<< endl;
	delete[]AnswerMulModule;
	cout << "Возводим число А в квадрат по модулю М:" << endl;
	int* AnswerPowerToSquareModul = PowerToSquareModul(ModuleA, integ_M, m_length, m_length, integ_Myu, myu_length);
	cout << "Результат возведения числа А в квадрат по модулю М:" << endl;
	for (int i = 0; i < m_length; i++)
	{
		cout << AnswerPowerToSquareModul[i] << "  ";
	}
	cout << endl;
	string Answer6 = ConvertNumberToStr(AnswerPowerToSquareModul, m_length);
	cout << Answer6 << endl;
	cout << "Возводим число А в степень, равную числу В, по модулю:" << endl;
	int* AnswerLongPowerMod = LongModPowerBarret(ModuleA, integ_B, integ_M, integ_Myu, m_length, b_length, m_length, myu_length);
	cout << "Результат возведения числа А в степень, равную числу В, по модулю:" << endl;
	for (int i = 0; i < m_length; i++)
	{
		cout << AnswerLongPowerMod[i] << "  ";
	}
	cout << endl;
	string Answer7 = ConvertNumberToStr(AnswerLongPowerMod, m_length);
	cout << Answer7 << endl;
	delete[]AnswerLongPowerMod;
	delete[]ModuleA;
	delete[]ModuleB;
	cout << endl<< endl;
	/*cout << "Ищем НСД чисел А и В:" << endl;
	if (CompareNum(integ_A, integ_B, a_length, b_length) == 0)
	{
		int* AnswerGCD = GCD(integ_B, integ_A, b_length, a_length);
	}
	int* AnswerGCD = GCD(integ_A, integ_B, a_length, b_length);
	for (int j = 0; j < answer_gcd_length; j++)
	{
		cout << AnswerGCD[j] << "  ";
	}
	cout << endl;
	string Answer8 = ConvertNumberToStr(AnswerGCD, answer_gcd_length);
	cout << Answer8 << endl;
	cout << endl << endl;
	cout << "Ищем НСК чисел А и В:" << endl;
	int* AnswerLCM = LCM(integ_A, integ_B, AnswerGCD, a_length, b_length, answer_gcd_length);
	for (int i = 0; i < 2 * Max(a_length, b_length); i++)
	{
		cout << AnswerLCM[i] << "  ";
	}
	cout << endl;
	string Answer9 = ConvertNumberToStr(AnswerLCM, 2 * Max(a_length, b_length));
	cout << Answer9 << endl;
	cout << endl << endl;*/
	/*cout << "===========================================================================";
	cout << endl;
	cout << "Проверки правильности выполнения" << endl;
	cout << "Пункт 1: (a+b)*c mod n= c*(a+b) mod n= a*c+ b*c mod n" << endl;
	string c;
	int c_length;
	int C[1000];
	int* integ_C = C;
	cout << "Число c:" << endl;
	cin >> c;
	c_length = c.length();
	integ_C = ConvertStrToNumber(c, c_length);
	cout << "Число C:" << endl;
	for (i = 0; i < c_length; i++)
	{
		cout << integ_C[i] << " ";
	}
	cout << endl;
	cout << "Решаем выражение (a+b)*c" << endl;
	int* AnswerAdd1 = LongAdd(integ_A, integ_B, a_length, b_length);
	cout << "Результат суммирования чисел А и В:" << endl;
	int AnswerAdd1_length;
	if (AnswerAdd1[Max(a_length, b_length) + 1] == 100)
	{
		AnswerAdd1_length = Max(a_length, b_length) + 1;
		for (int i = 0; i < Max(a_length, b_length) + 1; i++)
		{
			cout << AnswerAdd1[i] << "  ";
		}
		cout << endl;
	}
	else if (AnswerAdd1[Max(a_length, b_length) + 1] == 0)
	{
		AnswerAdd1_length = Max(a_length, b_length);
		for (int i = 0; i < Max(a_length, b_length); i++)
		{
			cout << AnswerAdd1[i] << "  ";
		}
	}
	int* AnswerMul1 = LongMul(AnswerAdd1, integ_C, AnswerAdd1_length, c_length);
	cout << "Результат выражения (а+b)*c :" << endl;
	string equation1 = ConvertNumberToStr(AnswerMul1, 2 * Max(AnswerAdd1_length, c_length));
	while (equation1.at(0) == '0')
	{
		equation1.erase(0, 1);
	}
	cout << equation1 << endl;
	cout << endl;
	cout << "Решаем выражение c*(a+b)" << endl;
	cout << "Длина ответа A+B = " << AnswerAdd1_length << endl;
	int* AnswerAdd3 = LongAdd(integ_A, integ_B, a_length, b_length);
	/*cout << "Число C:" << endl;
	for (i = 0; i < c_length; i++)
	{
		cout << integ_C[i] << " ";
	}
	cout << endl;*/
	/*cout << "Результат суммирования чисел А и В:" << endl;
	int AnswerAdd3_length;
	if (AnswerAdd3[Max(a_length, b_length) + 1] == 100)
	{
		AnswerAdd3_length = Max(a_length, b_length) + 1;
	}
	else if (AnswerAdd3[Max(a_length, b_length) + 1] == 0)
	{
		AnswerAdd3_length = Max(a_length, b_length);
	}
	for (i = 0; i < AnswerAdd3_length; i++)
	{
		cout << AnswerAdd3[i] << " ";
	}
	cout << endl;
	int* AnswerMul2;
	if (AnswerAdd3_length > c_length)
	{
		AnswerMul2 = LongMul(AnswerAdd3, integ_C, AnswerAdd3_length, c_length);
	}
	else
	{
		AnswerMul2 = LongMul(integ_C, AnswerAdd3, c_length, AnswerAdd3_length);
	}
	//AnswerMul2 = LongMul(integ_C, AnswerAdd3, c_length, AnswerAdd3_length);
	for (int i = 0; i < 2 * Max(AnswerAdd3_length, c_length); i++)
	{
		cout << AnswerMul2[i] << "  ";
	}
	cout << endl;
	cout << "Результат выражения c*(а+b) :" << endl;
	string equation2 = ConvertNumberToStr(AnswerMul2, 2 * Max(AnswerAdd1_length, c_length));
	while (equation2.at(0) == '0')
	{
		equation2.erase(0, 1);
	}
	cout << equation2 << endl;
	cout << endl;
	cout << "Решаем выражение a*c+b*c" << endl;
	int* AnswerMul3 = LongMul(integ_A, integ_C, a_length, c_length);
	int* AnswerMul4 = LongMul(integ_B, integ_C, b_length, c_length);
	int* AnswerAdd2 = LongAdd(AnswerMul3, AnswerMul4, 2 * Max(a_length, c_length), 2 * Max(b_length, c_length));
	int AnswerAdd2_length;
	if (AnswerAdd2[Max(2 * Max(a_length, c_length), 2 * Max(b_length, c_length)) + 1] == 100)
	{
		AnswerAdd2_length = Max(2 * Max(a_length, c_length), 2 * Max(b_length, c_length)) + 1;
	}
	else if (AnswerAdd2[Max(2 * Max(a_length, c_length), 2 * Max(b_length, c_length)) + 1] == 0)
	{
		AnswerAdd2_length = Max(2 * Max(a_length, c_length), 2 * Max(b_length, c_length));
	}
	string equation3 = ConvertNumberToStr(AnswerAdd2, AnswerAdd2_length);
	while (equation3.at(0) == '0')
	{
		equation3.erase(0, 1);
	}
	cout << equation3 << endl;
	cout << endl;
	delete[]AnswerAdd1;
	delete[]AnswerAdd2;
	delete[]AnswerAdd3;
	delete[]AnswerMul1;
	delete[]AnswerMul2;
	delete[]AnswerMul3;
	delete[]AnswerMul4;*/
	return 0;
}
