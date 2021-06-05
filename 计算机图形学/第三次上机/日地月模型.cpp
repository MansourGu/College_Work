#include <gl/glut.h>
void Initial()
{
	glEnable(GL_DEPTH_TEST);       // ������Ȳ���
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f );	//����Ϊ��ɫ
}

void ChangeSize(int w, int h)
{
	if(h == 0)	h = 1;
	glViewport(0, 0, w, h);               // ���������ߴ�
	glMatrixMode(GL_PROJECTION);    // ָ����ǰ����ͶӰ�����ջ
	glLoadIdentity();                   // ����ͶӰ����

	GLfloat fAspect;
	fAspect = (float)w/(float)h;            // ���������Ŀ�߱�
	gluPerspective(45.0, fAspect, 1.0, 500.0); // ָ��͸��ͶӰ�Ĺ۲�ռ�
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Display(void)
{
	static float fElect1 = 0.0f;           // ��̫����ת�ĽǶ�
	static float fElect2 = 0.0f;           // �Ƶ�����ת�ĽǶ�
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�����ɫ����Ȼ�����

	glMatrixMode(GL_MODELVIEW);  // ָ����ǰ����ģ����ͼ�����ջ
	glLoadIdentity();                  // ����ģ����ͼ����
	glTranslatef(0.0f, 0.0f, -250.0f);	   //��ͼ����z�Ḻ���ƶ�

	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidSphere(12.0f, 15, 15);      // ����̫��

	glColor3f(0.0f, 0.0f, 1.0f);
	glPushMatrix();                  // ���浱ǰ��ģ����ͼ����
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);   // ��y����תһ���ĽǶ�
	glTranslatef(90.0f, 0.0f, 0.0f);       // ƽ��һ�ξ���
	glutSolidSphere(6.0f, 15, 15);       // ��������
	glColor3f(0.5f, 0.5f, 0.5f);
	glRotatef(fElect2, 0.0f, 1.0f, 0.0f);
	glTranslatef(-50.0f, 0.0f, 0.0f);
	glutSolidSphere(3.0f, 15, 15);       // ��������

	fElect1 += 5.0f;     // ������ת��������������Ч��
	if(fElect1 > 360.0f)	fElect1 = 5.0f;
	fElect2 += 10.0f;     // ������ת��������������Ч��
	if (fElect2 > 360.0f)	fElect2 = 10.0f;
	glutSwapBuffers();
}

void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("�յ��¶���ʾ��");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(Display);
	glutTimerFunc(500, TimerFunc, 1);     //ָ����ʱ���ص�����
	Initial();
	glutMainLoop();
	return 0;
}