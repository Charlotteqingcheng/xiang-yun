// ConsoleApplication1(全国交通咨询模拟).cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stdlib.h>
#include<stack>
#include<string>
#include<fstream>
#include<limits.h>
#include <cstdio>
#define MAX 100
using namespace std;
int op=0;
const int MAXSIZE = 10;
template<class datatype>
class costs
{
public:
	costs(datatype a[], int n, int e);//构造函数，有n个城市e个两城市之间的路线
	~costs(){}
	void savemoney(int v,int w);//最省钱到达见170页
	void savetime(int v, int w);//最省时到达见170页
private:
	datatype city[MAXSIZE];//存放城市的数组
	int cost[MAXSIZE][MAXSIZE];//存放花费的数组
	int time[MAXSIZE][MAXSIZE];//存放时间的数组
	int citynum, costnum;//城市数，花费数
};
template<class datatype>
costs<datatype>::costs(datatype a[], int n, int e)
{
	citynum = n; costnum = e;
	int i, j, k=0,m=0,o=0;
	ifstream input,input1;//文件形式输入数据
	for (i = 0; i < citynum; i++)
		city[i] = a[i];
	for (i = 0; i < citynum; i++)
	{
		for (j = 0; j < citynum; j++)
		{
			if (i == j)
			{
				cost[i][j] = MAX;
				time[i][j] = MAX;
			}
			else
			{
				cost[i][j] = MAX;
				time[i][j] = MAX;
			}
		}
	}

			/*if (p == "火车")
	{
			input.open("input1.txt");//文件形式输入数据
			input>>cost[0][1]>>cost[0][2]>>cost[0][3];
			input>>cost[2][3]>>cost[1][3]>>cost[1][4];
			input>>cost[1][5]>>cost[3][5]>>cost[4][5];
			input>>time[0][1]>>time[0][2]>>time[0][3];
			input>>time[2][3]>>time[1][3]>>time[1][4];
			input>>time[1][5]>>time[3][5]>>time[4][5];
				input.close();
		
	}*/
	/*if(p=="飞机")
	{
		input1.open("input1.txt");//文件形式输入数据
		input1>>cost[0][1]>>cost[0][2]>>cost[0][3];
		input1>>cost[2][3]>>cost[1][3]>>cost[1][4];
		input1>>cost[1][5]>>cost[3][5]>>cost[4][5];
		input1>>time[0][1]>>time[0][2]>>time[0][3];
		input1>>time[2][3]>>time[1][3]>>time[1][4];
		input1>>time[1][5]>>time[3][5]>>time[4][5];
					input1.close();
		
	}*/
	if (op==0)
	{
			cost[0][1] = 5, cost[0][2] = 3, cost[0][3] = 8;
			cost[2][3] = 6, cost[1][3] = 5, cost[1][4] = 3;
			cost[1][5] = 3, cost[3][5] = 4, cost[4][5] = 2;
			time[0][1] = 50, time[0][2] = 30, time[0][3] = 80;
			time[2][3] = 60, time[1][3] = 80, time[1][4] = 30;
			time[1][5] = 60, time[3][5] = 40, time[4][5] = 20;
			op++;
	}
	else
	{
		cost[0][1] = 50, cost[0][2] = 30, cost[0][3] = 80;
		cost[2][3] = 60, cost[1][3] = 50, cost[1][4] = 30;
		cost[1][5] = 30, cost[3][5] = 40, cost[4][5] = 20;
		time[0][1] = 5, time[0][2] = 3, time[0][3] = 8;
		time[2][3] = 6, time[1][3] = 15, time[1][4] = 3;
		time[1][5] = 13, time[3][5] = 4, time[4][5] = 2;
	}
	/*for (k = 0; k < costnum; k++)
		{
			cin >> m >> o>>cost[m][o+1];//输入从第i城市到第j城市(这里手动输入出现了致命错误，问老师//
		}*/
}
template<class datatype>
void costs<datatype>::savemoney(int x,int y)//迪杰斯特拉算法//
{
	int D[10];//保存最短路径长度
	int p[10][10];//路径
	int final[10] = {0};//若final[i] = 1则说明 顶点vi已在集合S中
	int n = citynum;//顶点个数
	int v0 = x;//源点
	int v, w,k=0;
	string dish[6][6] = { " " };
	dish[0][1] = "北京 广州", dish[0][2] = "北京 沈阳", dish[0][3] = "北京 厦门", dish[0][4] = "北京 广州", dish[0][5] = "北京 广州 海南";
	dish[1][2] = " 无 ", dish[1][3] = "广州 厦门", dish[1][4] = "广州 上海", dish[1][5] = "广州 海南";
	dish[2][3] = "沈阳 厦门", dish[2][4] = " 无 ", dish[2][5] = "沈阳 厦门 海南";
	dish[3][4] = " 无 ", dish[3][5] = "厦门 海南";
	dish[4][5] = "上海 海南";
	for (v = 0; v < n; v++) //循环 初始化
	{
		final[v] = 0; D[v] = cost[v0][v];
		for (w = 0; w < n; w++) p[v][w] = 0;//设空路径
		if (D[v] < MAX) { p[v][v0] = 1; p[v][v] = 1; }
	}
	D[v0] = 0; final[v0] = 1; //初始化 v0顶点属于集合S
	//开始主循环 每次求得v0到某个顶点v的最短路径 并加v到集合S中
	for (int i = 1; i < n; i++)
	{
		int min = MAX;
		for (w = 0; w < n; w++)
		{
			//核心过程--选点
			if (!final[w]) //如果w顶点在V-S中
			{
				//这个过程最终选出的点 应该是选出当前V-S中与S有关联边
				//且权值最小的顶点 书上描述为 当前离V0最近的点
				if (D[w] < min) { v = w; min = D[w]; }
			}
		}
		final[v] = 1; //选出该点后加入到合集S中
		for (w = 0; w < n; w++)//更新当前最短路径和距离
		{
			/*在此循环中 v为当前刚选入集合S中的点
			则以点V为中间点 考察 d0v+dvw 是否小于 D[w] 如果小于 则更新
			比如加进点 3 则若要考察 D[5] 是否要更新 就 判断 d(v0-v3) + d(v3-v5) 的和是否小于D[5]
			*/
			if (!final[w] && (min + cost[v][w] < D[w]))
			{
				D[w] = min + cost[v][w];
				// p[w] = p[v];
				p[w][w] = 1; //p[w] = p[v] +　[w]
			}
		}
	}
	cout << endl;
	cout << "经过的城市为：" << dish[x][y] << endl;
	cout << "最少需要" << D[y] <<"元旅费才能到达"<< endl;

}
template<class datatype>
void costs<datatype>::savetime(int x, int y)//迪杰斯特拉算法//
{
	int D[10];//保存最短路径长度
	int p[10][10];//路径
	int final[10] = { 0 };//若final[i] = 1则说明 顶点vi已在集合S中
	int n = citynum;//顶点个数
	int v0 = x;//源点
	int v, w, k;
	string dish[6][6] = { " " };
	dish[0][1] = "北京 广州", dish[0][2] = "北京 沈阳", dish[0][3] = "北京 厦门", dish[0][4] = "北京 广州", dish[0][5] = "北京 上海 海南";
	dish[1][2] = " 无 ", dish[1][3] = "广州 厦门", dish[1][4] = "广州 上海", dish[1][5] = "广州 海南";
	dish[2][3] = "沈阳 厦门", dish[2][4] = " 无 ", dish[2][5] = "沈阳 厦门 海南";
	dish[3][4] = " 无 ", dish[3][5] = "厦门 海南";
	dish[4][5] = "上海 海南";
	for (v = 0; v < n; v++) //循环 初始化
	{
		final[v] = 0; D[v] = time[v0][v];
		for (w = 0; w < n; w++) p[v][w] = 0;//设空路径
		if (D[v] < MAX) { p[v][v0] = 1; p[v][v] = 1; }
	}
	D[v0] = 0; final[v0] = 1; //初始化 v0顶点属于集合S
	//开始主循环 每次求得v0到某个顶点v的最短路径 并加v到集合S中
	for (int i = 1; i < n; i++)
	{
		int min = MAX;
		for (w = 0; w < n; w++)
		{
			//核心过程--选点
			if (!final[w]) //如果w顶点在V-S中
			{
				//这个过程最终选出的点 应该是选出当前V-S中与S有关联边
				//且权值最小的顶点 书上描述为 当前离V0最近的点
				if (D[w] < min) { v = w; min = D[w]; }
			}
		}
		final[v] = 1; //选出该点后加入到合集S中
		for (w = 0; w < n; w++)//更新当前最短路径和距离
		{
			/*在此循环中 v为当前刚选入集合S中的点
			则以点V为中间点 考察 d0v+dvw 是否小于 D[w] 如果小于 则更新
			比如加进点 3 则若要考察 D[5] 是否要更新 就 判断 d(v0-v3) + d(v3-v5) 的和是否小于D[5]
			*/
			if (!final[w] && (min + time[v][w] < D[w]))
			{
				D[w] = min + time[v][w];
				// p[w] = p[v];
				p[w][w] = 1; //p[w] = p[v] +　[w]
			}
		}
	}
	cout << endl;
	cout << "经过的城市为：" << dish[x][y] << endl;
	cout << "最快需要" << D[y] << "分钟才能到达" << endl;

}
/*void costs<datatype>::savemoney()无效代码
{
	int i, j, k,dist[6][6] = { 0 };
	string path[6][6] = { "" };
	for (i = 0; i < citynum; i++)
		for (j = 0; j < citynum; j++)
		{
		dist[i][j] = cost[i][j];
		if (dist[i][j] != 100)
			path[i][j] = city[i] + city[j];
		else path[i][j] = "";
		}
	for (k = 0; k < citynum; k++)
	{
		for (i = 0; i < citynum; i++)
			for (j = 0; j < citynum; j++)
				if (dist[i][k] + dist[k][j] < dist[i][j])
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = path[i][k] + path[k][j];
				}
		
	}
	for (i = 0; i < citynum; i++)
	{
		for (j = 0; j < citynum; j++)
			cout << dist[i][j] << "";
		cout << endl;
	}
	for (i = 0; i < citynum; i++)
	{
		for (j = 0; j < citynum; j++)
			cout << path[i][j] << "";
		cout << endl;
	}
}*/
/*void costs<datatype>::savemoney(int v,int z)
{
	int i, k,dist[6] = { 0 };
	string path[9] = { "" };
	int s[10] = { 0 },num;
	for (i = 0; i < citynum; i++)
	{
		dist[i] = cost[v][i];
		if (dist[i] != 100)
			path[i] = city[v] + city[i];
		else path[i] = "";
	}
	s[0] = v;
	dist[v] = 0;
	num = 1;
	while (num < citynum)
	{
		for (k = 0, i = 0; i < citynum; i++)
		{
			if ((dist[i] != 0) && (dist[i] < dist[k]))
				k = i;
		}
		cout << dist[k] << path[k];
		s[num++] = k;
		for(i=0;i<citynum;i++)
			if (dist[i] > dist[k] + cost[k][i])
			{
				dist[i] = dist[k] + cost[k][i];
				path[i] = path[k] + city[i];
			}
		dist[k] = 0;
	}

}*/
void insertcity()//城市编辑功能
{
	int i, c,d,f,g;
	string a,b,e;
	string city[10] = { "北京","广州","沈阳","厦门","上海","海南" };//城市
	string cost[20] = { "a,b 5","a,c 3","a,d 8","c,d 6","b,d 5","b,e 3","b,f 3","d,f 4","e,f 2" };//边的信息
	cout << "本次乘坐涉及到到的城市如下所示" << endl;
	for (i = 0; i < 6; i++)
		cout << city[i] << " ";
	cout << endl;
	cout << "是否要对城市信息进行编辑？" << endl;
	cin >> a;
	if (a == "是")
	{
		cout << "请根据城市信息表写出您想进行的操作（本系统只提供添加和删除功能）" << endl;
		cin >> b;
		if (b == "添加")
		{
			cout << "请问您想要添加几个城市：";
			cin >> c;
			cout << endl;
			cout << "请问您想要添加的城市是什么：";
			for (d = 6; d < c + 6; d++)
				cin>>city[d];
			cout << "添加之后的城市信息为" << endl;
			for (i = 0; i < c + 6; i++)
				cout << city[i] << " ";
		}
		if (b == "删除")
		{
			cout << "请问您想要删除第几个城市（按城市表从左到右算）：";
			cin >> f;
			for (g = f; g < 6; g++)
				city[g - 1] = city[g];
			cout << "删除之后的城市信息为" << endl;
			for (i = 0; i < 5; i++)
				cout << city[i] << " ";
		}
	}
	cout << endl;
}
void insertvehicle()
{
	int i, j,SIZE=6,c,d,f,g,h,k,l,q=0,r=0;//SIZE用来记录一下时刻表的矩阵大小
	string a, b, e;
	ifstream input2;
	/*input2.open("input2.txt");
	for(q=0;q<10;q++)
	{	for(r=0;r<6;r++)
		input2>>traintable[q][r];
	}
	for(q=0;q<10;q++)
	{	for(r=0;r<6;r++)
		input2>>planeable[q][r];
	}
	input2.close();
	*/
	string traintimetable[10][6] =
	{ "车次","始发站","始发时间","终点站","到达时间","经过站",
	 "NO.1","北京","8:00","海南","9:40","广州·上海",
	 "NO.2","北京","8:00","海南","10:00","厦门",
	 "NO.3","广州","9:20","海南","9:50","无",
	 "NO.4","广州","9:20","厦门","10:10","无",
	 "NO.5","北京","8:00","厦门","9:30","沈阳" };
	string planetimetable[10][6]=
	{ "机次","始发点","始发时间","终点站","到达时间","经过点",
     "NO.1","北京","8:00","海南","8:10","广州·上海",
     "NO.2","北京","8:00","海南","8:12","厦门",
     "NO.3","广州","8:10","海南","8:13","无",
     "NO.4","广州","8:10","厦门","8:15","无",
     "NO.5","北京","8:00","厦门","8:09","沈阳" };
	cout << "本次乘坐可参照的火车时刻表如下" << endl;
	for (i = 0; i < SIZE; i++)
	{

		for (j = 0; j < SIZE; j++)
		{
			if (i == 0 || j == 0)
				cout << traintimetable[i][j] << "  ";
			else
				cout << traintimetable[i][j] << "     ";
		}

		cout << endl;
	}
	cout << "本次只设立一个中转站：广州" << endl;//中转站的时间已经根据时刻表自动加入到矩阵中，中转时间：火车30分钟飞机10分钟
	cout << "本次乘坐可参照的飞机时刻表如下" << endl;
	for (i = 0; i < SIZE; i++)
	{

		for (j = 0; j < SIZE; j++)
		{
			if (i == 0 || j == 0)
				cout << planetimetable[i][j] << "  ";
			else
				cout << planetimetable[i][j] << "     ";
		}
		cout << endl;
	}
	cout << "本次只设立一个中转站：广州" << endl;//中转站的时间已经根据时刻表自动加入到矩阵中，中转时间：火车30分钟飞机10分钟
	cout << "是否要对时刻表信息进行编辑？" << endl;
	cin >> a;
	if (a == "是")
	{
		cout << "下面将进行对火车时刻表的修改，如果不想修改请输入1" << endl;
		cin >> l;
		if (l == 1)
			goto o;
		cout << "请根据火车时刻表信息写出您想进行的操作（本系统只提供添加和删除功能）" << endl;
		cin >> b;
		if (b == "添加")
		{
			cout << "请问您想要添加几辆火车：";
			cin >> c;
			cout << endl;
			cout << "请根据时刻表添加你想要增加的火车时刻表信息：";
			for (d = SIZE; d < c + SIZE; d++)
				for (h = 0; h < SIZE; h++)
					cin >> traintimetable[d][h];
			cout << "添加之后的火车时刻表信息为" << endl;
			for (i = 0; i < SIZE+c; i++)
			{

				for (j = 0; j < SIZE; j++)
				{
					if (i == 0 || j == 0)
						cout << traintimetable[i][j] << "  ";
					else
						cout << traintimetable[i][j] << "     ";
				}
				cout << endl;
			}
		}
		if (b == "删除")
		{
			cout << "请问您想要删除第几辆火车（按时刻表从上到下算）：";
			cin >> f;
			for (g = f; g < 6; g++)
				for(k=0;k<SIZE;k++)
					traintimetable[g - 1][k] = traintimetable[g][k];
			cout << "删除之后的火车时刻表信息为" << endl;
			for (i = 0; i < SIZE-1; i++)
			{

				for (j = 0; j < SIZE; j++)
				{
					if (i == 0 || j == 0)
						cout << traintimetable[i][j] << "  ";
					else
						cout << traintimetable[i][j] << "     ";
				}
				cout << endl;
			}
		}
	o:
		cout << "请根据飞机时刻表信息写出您想进行的操作（本系统只提供添加和删除功能）" << endl;
		cin >> b;
		if (b == "添加")
		{
			cout << "请问您想要添加几辆飞机：";
			cin >> c;
			cout << endl;
			cout << "请根据时刻表添加你想要增加的飞机时刻表信息：";
			for (d = SIZE; d < c + SIZE; d++)
				for (h = 0; h < SIZE; h++)
					cin >> planetimetable[d][h];
			cout << "添加之后的飞机时刻表信息为" << endl;
			for (i = 0; i < SIZE + c; i++)
			{

				for (j = 0; j < SIZE; j++)
				{
					if (i == 0 || j == 0)
						cout << planetimetable[i][j] << "  ";
					else
						cout << planetimetable[i][j] << "     ";
				}
				cout << endl;
			}
		}
		if (b == "删除")
		{
			cout << "请问您想要删除第几个飞机（按时刻表从上到下算）：";
			cin >> f;
			for (g = f+1; g < 6; g++)
				for (k = 0; k < SIZE; k++)
					planetimetable[g - 1][k] = planetimetable[g][k];
			cout << "删除之后的飞机时刻表信息为" << endl;
			for (i = 0; i < SIZE - 1; i++)
			{

				for (j = 0; j < SIZE; j++)
				{
					if (i == 0 || j == 0)
						cout << planetimetable[i][j] << "  ";
					else
						cout << planetimetable[i][j] << "     ";
				}
				cout << endl;
			}
		}
	}
	cout << endl;
}
void ask(costs<string> TRAIN,costs<string> PLANE)
{
	int v = 0, k = 0, w = 0;
	string p, l;
	cout << "请将您最后确定的完整信息输入到下面的表格中（因输入过于麻烦这里管理员将测试结果直接写入系统，请见谅）" << endl;
	while (1)
	{
		cout << "请您输入想要乘坐的交通工具" << endl;
		cin >> p;
		if (p == "火车")
		{
			cout << "请根据城市信息从左到右输入你想要出发的第几城市（起始站1~5起点，一定要比终点小，否则后果自负）" << endl;
			cin >> v;
			v--;
			cout << "请根据城市信息从左到右输入你想要到达的第几城市（终点站2~6）" << endl;
			cin >> w;
			w--;
			while (1)
			{
				cout << "请输入你想要的最优决策（省钱或最快）" << endl;
				cin >> l;
				if (l == "省钱")
				{
					TRAIN.savemoney(v, w);
					break;
				}
				if (l == "最快")
				{
					TRAIN.savetime(v, w);
					break;
				}
				cout << "错误！请重新填写" << endl;
			}
			break;
		}
		if (p == "飞机")
		{
			cout << "请根据城市信息从左到右输入你想要出发的第几城市（起始站）" << endl;
			cin >> v;
			v--;
			cout << "请根据城市信息从左到右输入你想要到达的第几城市（终点站）" << endl;
			cin >> w;
			w--;
			while (1)
			{
				cout << "请输入你想要的最优决策（省钱或最快）" << endl;
				cin >> l;
				if (l == "省钱")
				{
					PLANE.savemoney(v, w);
					break;
				}
				if (l == "最快")
				{
					PLANE.savetime(v, w);
					break;
				}
				cout << "错误！请重新填写" << endl;
			}
			break;
		}
		cout << "错误！请重新填写" << endl;
	}
}
void menu(costs<string> TRAIN, costs<string> PLANE)
{
	cout << "\t                                  ***********************************" << "\n";
	cout << "\t                                  *  0.退出系统                     *" << "\n";
	cout << "\t                                  *  1.城市编辑                     *" << "\n";
	cout << "\t                                  *  2.时刻表编辑                   *" << "\n";
	cout << "\t                                  *  3.咨询信息                     *" << "\n";
	cout << "\t                                  ***********************************" << "\n";
	while (1)
	{
		int choice = 3;
		cout << "   请输入你想使用的功能：";
		cin >> choice;
		if (choice == 0)
			break;
		switch (choice)
		{
		case 1:insertcity();
			break;//更改城市信息
		case 2:insertvehicle();
			break;//更改时刻表信息
		case 3:ask(TRAIN, PLANE);
			break;//咨询信息
		default:
		{
			cout << "选择错误，请重新选择" << endl;
		}
		}
	}
	cout << "                                          *感谢使用本系统，再见！*" << endl;
}
int main()
{
	system("color 74");
	string city[10] = { "北京","广州","沈阳","厦门","上海","海南" };//城市
	costs<string> TRAIN(city, 6, 9);//载入火车信息
	costs<string> PLANE(city, 6, 9);//载入飞机信息
	system("cls");//清理页面
	menu(TRAIN, PLANE);
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
