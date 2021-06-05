#include<GL/glut.h>



// 将立方体的八个顶点保存到一个数组里面

static const float vertex_list[][3] =
{
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
};

// 将要使用的顶点的序号保存到一个数组里面

static const GLint index_list[][2] =
{
	{ 0, 1},
	{ 2, 3},
	{ 4, 5},
	{ 6, 7},
	{ 0, 2},
	{ 1, 3},
	{ 4, 6},
	{ 5, 7},
	{ 0, 4},
	{ 1, 5},
	{ 7, 3},
	{ 2, 6}
};//边表

// 绘制立方体

void Paint(void)
{
	int i, j;

	glBegin(GL_LINES);
	for (i = 0; i < 12; ++i) // 12 条线段

	{
		for (j = 0; j < 2; ++j) // 每条线段 2个顶点

		{
			glVertex3fv(vertex_list[index_list[i][j]]);
		}
	}
	glEnd();
}

static float rotate = 0;

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glRotatef(rotate, 0, 1, 0);//绕y旋转
	glRotatef(rotate, 1, 0, 0);//绕x旋转
	glColor3f(1, 1, 0);
	Paint();
	glPopMatrix();
	rotate += 1;
	if (rotate > 360)
	{
		rotate = 0;
	}
	glutSwapBuffers();
}

int main()
{
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Cube");
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutMainLoop();
}