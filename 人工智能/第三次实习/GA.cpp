
#include<stdio.h>
#include<time.h>
#include<windows.h>
#define T 200	//��������
#define N 20	//Ⱥ�����
#define INT 4	//�������򳤶�
#define FLOAT 0	//С�����򳤶�
#define MUTATE 0.005	//����ͻ����

int t = 0;	//��������
int gene[N][(INT + FLOAT)];	//����
double value[N];	//����ֵ
double ratio[N];	//��Ӧ�ȸ�������
int pair[N];	//�����Թ���
int totalRate = 0;

void InitGroup();
double GetValue(int[], int);
int Mi(int, int);
void SortGroup();
void Output();
double Function(float);
void PairGroup();
void GeneMutate();
void Answer();

int main() {
	InitGroup();
	Output();
	while ((t++) != T) {
		GeneMutate();
		SortGroup();
		PairGroup();
	}
	SortGroup();
	Output();
	Answer();
}

//Ŀ�꺯��
double Function(double a) {
	return 15*a - a*a;
}

//��ʼ����Ⱥ
void InitGroup() {
	for (int i = 1; i <= N; i++) {
		totalRate += i * i;
	}
	srand((unsigned)time(0));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < (INT + FLOAT); j++) {
			gene[i][j] = rand() % 2;
		}
	}
	for (int i = 0; i < N; i++) {
		if (i == 0) {
			ratio[i] = (i + 1)*(i + 1) / (double)totalRate;
		}
		else {
			ratio[i] = (i + 1)*(i + 1) / (double)totalRate;
			ratio[i] += ratio[i - 1];
		}
		//printf("%f\n",ratio[i]);
	}
	for (int i = 0; i < N; i++) {
		value[i] = Function(GetValue(gene[i], 1));
	}
}

//�����Ⱥ��Ϣ
void Output() {

	printf("�������\n");
	for (int i = 0; i < N; i++) {
		printf("��");
		for (int j = 0; j < (INT + FLOAT); j++) {
			if (j == INT) printf("��");
			else if (j == INT + FLOAT) printf("��,��");
			else if (j == INT * 2 + FLOAT) printf("��");
			printf("%d", gene[i][j]);
		}
		printf("��\n");
	}

	printf("������ֵ��\n");
	for (int i = 0; i < N; i++) {
		printf("%d: %f -> %.16f\n", i, GetValue(gene[i], 1), value[i]);
	}
}

//��a��b�η�
int Mi(int a, int b) {
	int ans = 1;
	for (int i = 0; i < b; i++) {
		ans *= a;
	}
	return ans;
}

//��ʮ����ֵ
double GetValue(int a[(INT + FLOAT)], int n) {
	int v = 0;
	double ans;
	if (n == 1) {
		for (int i = 1; i <= INT + FLOAT; i++) {
			if (a[i - 1] != 0) v += Mi(2, INT + FLOAT - i);
		}
		ans = v / (double)Mi(2, FLOAT);
	}
	return ans;
}

//������Ӧ�Ȳ�����
void SortGroup() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - 1; j++) {
			if (value[j] > value[j + 1]) {
				double b = value[j];
				value[j] = value[j + 1];
				value[j + 1] = b;
				for (int k = 0; k < (INT + FLOAT); k++) {
					int a = gene[j][k];
					gene[j][k] = gene[j + 1][k];
					gene[j + 1][k] = a;
				}
			}
		}
	}
}

//����������� 
void PairGroup() {
	float b;
	for (int i = 0; i < N; i++) {
		b = rand() / (RAND_MAX + 1.0);
		for (int j = 0; j < N; j++) {
			if (ratio[j] >= b) {
				pair[i] = j;
			
				break;
			}
		}
	}
	int gene1[N][(INT + FLOAT)];
	for (int i = 0; i < N - 1; i += 2) {
		int pos = rand() % ((INT + FLOAT) - 1) + 1;
		
		for (int k = 0; k < (INT + FLOAT); k++) {
			gene1[i][k] = gene[pair[i]][k];
			gene1[i + 1][k] = gene[pair[i + 1]][k];
		}
		for (int j = 0; j < pos; j++) {
			int a = gene1[i][j];
			gene1[i][j] = gene1[i + 1][j];
			gene1[i + 1][j] = a;
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < (INT + FLOAT); j++) {
			gene[i][j] = gene1[i][j];
		}
	}
	for (int i = 0; i < N; i++) {
		value[i] = Function(GetValue(gene[i], 1));
	}
}

//����ͻ�� 
void GeneMutate() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < (INT + FLOAT); j++) {
			if (rand() / (RAND_MAX + 1.0) < MUTATE) {
				gene[i][j] = (gene[i][j] + 1) % 2;
			}
		}
	}
	for (int i = 0; i < N; i++) {
		value[i] = Function(GetValue(gene[i], 1));
	}
}

//����� 
void Answer() {
	printf("\n\n���ֵ�ǣ�%.16f\n", value[N - 1]);
	printf("��ʱ��x1=%f,", GetValue(gene[N - 1], 1));
	system("pause");
}