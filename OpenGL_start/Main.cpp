# include <GL/glut.h> 
# include <math.h>
const GLfloat  PI = 3.14159265358979323846f;


/* 初始化材料属性、光源属性、光照模型，打开深度缓冲区等 */
void init(void)
{
	//定义光源
	GLfloat light_position[] = { 0.6, 0.8, 1.0, 1.0 };//光源位置 定位光源
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };//环境光
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };//漫反射光
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };//镜面反射光
	GLfloat mat_shininess[] = { 50.0 };//设置材料反射指数
	GLfloat sun_mat_emission[] = { 0.3f, 0.0f, 0.0f, 1.0f };//定义材质的辐射广颜色，为偏红色
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, light_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
	glClearColor(0.0, 1.0, 1.0, 0.0); //设置背景色为青色
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

//球心坐标为（x，y，z），球的半径为radius，M，N分别表示球体的横纵向被分成多少份
//https://blog.csdn.net/nongfu_spring/article/details/12651373
void drawSphere(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat radius, GLfloat M, GLfloat N)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	float step_z = PI / M;
	float step_xy = 2 * PI / N;
	float x[4], y[4], z[4];
	float angle_z = 0.0;
	float angle_xy = 0.0;
	int i = 0, j = 0;
	glBegin(GL_POLYGON);
	for (i = 0; i < M; i++)
	{
		angle_z = i * step_z;

		for (j = 0; j < N; j++)
		{
			angle_xy = j * step_xy;
			x[0] = radius * sin(angle_z) * cos(angle_xy);
			y[0] = radius * sin(angle_z) * sin(angle_xy);
			z[0] = radius * cos(angle_z);
			x[1] = radius * sin(angle_z + step_z) * cos(angle_xy);
			y[1] = radius * sin(angle_z + step_z) * sin(angle_xy);
			z[1] = radius * cos(angle_z + step_z);
			x[2] = radius * sin(angle_z + step_z) * cos(angle_xy + step_xy);
			y[2] = radius * sin(angle_z + step_z) * sin(angle_xy + step_xy);
			z[2] = radius * cos(angle_z + step_z);
			x[3] = radius * sin(angle_z) * cos(angle_xy + step_xy);
			y[3] = radius * sin(angle_z) * sin(angle_xy + step_xy);
			z[3] = radius * cos(angle_z);
			for (int k = 0; k < 4; k++)
			{
				glVertex3f(xx + x[k], yy + y[k], zz + z[k]);
			}
		}
	}
	glEnd();
}

/*绘制一个球*/
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawSphere(0, 0, 0, 0.8, 100, 100);
	glFlush();
}

/* 定义 GLUT 的 reshape 函数，w、h 分别是输出图形的窗口的宽和高*/
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w,
			1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0); //建立平行视景体
	else
		glOrtho(-1.5 * (GLfloat)w / (GLfloat)h, 1.5 * (GLfloat)
			w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);     // GLUT 环境初始化
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH); // 显示模式初始化
	glutInitWindowSize(400, 400);       // 定义窗口大小
	glutInitWindowPosition(100, 100);   // 定义窗口位置  
	glutCreateWindow(argv[0]);   // 显示窗口,窗口标题为执行函数名
	init();
	glutSetWindowTitle("真实感图形");
	glutDisplayFunc(display); 	// 注册 OpenGL 绘图函数(一种特殊的调用方式,下同) 
	glutReshapeFunc(reshape);   // 注册窗口大小改变时的响应函数
	glutMainLoop();      // 进入 GLUT 消息循环，开始执行程序
	return 0;
	// http://www.noobyard.com/article/p-zwctpzfl-gr.html
}
