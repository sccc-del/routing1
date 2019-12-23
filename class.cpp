#include"class.h"
#include<fstream>
Graph_DG::Graph_DG(int vexnum, int edge) {
	//初始化路由器数和路径数
	this->vexnum = vexnum;
	this->edge = edge;
	//为邻接矩阵开辟空间和赋初值

	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			arc[i][j] = INT_MAX;
		}
		dis[i].path = "";
		dis[i].value = INT_MAX;
		dis[i].visit = true;
	}

}

//析构函数
Graph_DG::~Graph_DG() {
	delete[] dis;
	for (int i = 0; i < this->vexnum; i++) {
		delete this->arc[i];
	}
	delete arc;
}

// 判断我们每次输入的的路径的信息是否合法
//路由器从1开始编号
bool Graph_DG::check_edge_value(int start, int end, int weight) {
	if (start<1 || end<1 || start>vexnum || end>vexnum || weight < 0) {
		return false;
	}
	return true;
}

void Graph_DG::createGraph() {
	cout << "请输入每条路径的起点和终点（路由器编号从1开始）以及其权重" << endl;
	int start;
	int end;
	int weight;
	int count = 0;
	while (count != this->edge) {
		cin >> start >> end >> weight;
		//首先判断路径的信息是否合法
		while (!this->check_edge_value(start, end, weight)) {
			cout << "输入的路径的信息不合法，请重新输入" << endl;
			cin >> start >> end >> weight;
		}
		//对邻接矩阵对应上的路由器赋值
		arc[start - 1][end - 1] = weight;
		//由于是无向图，补全矩阵
		arc[end - 1][start - 1] = weight;
		++count;
	}
}

void Graph_DG::print() {
	cout << "局域网图的邻接矩阵为：" << endl;
	int count_row = 0; //打印行的标签
	int count_col = 0; //打印列的标签
	//开始打印
	while (count_row != this->vexnum) {
		count_col = 0;
		while (count_col != this->vexnum) {
			if (arc[count_row][count_col] == INT_MAX)
				cout << "∞" << " ";
			else
				cout << arc[count_row][count_col] << " ";
			++count_col;
		}
		cout << endl;
		++count_row;
	}
}
void Graph_DG::work_begin(int begin) {
	int i;
	for (i = 0; i < this->vexnum; i++) {
		//设置当前的路径
		dis[i].path = "v" + to_string(begin) + "-->v" + to_string(i + 1);
		dis[i].value = arc[begin - 1][i];
		dis[i].visit = false;
	}
	//设置起点路由器的到末点路由器的路径为0
	dis[begin - 1].value = 0;
	dis[begin - 1].visit = true;
}



void Graph_DG::Dijkstra() {
	int i;
	int count = 1;
	//计算剩余的路由器的最短路径（剩余this->vexnum-1个顶点）
	while (count != this->vexnum) {
		//temp用于保存当前dis数组中最小的那个下标
		//min记录的当前的最小值
		int temp = 0;
		int min = INT_MAX;
		for (i = 0; i < this->vexnum; i++) {
			if (!dis[i].visit && dis[i].value < min) {
				min = dis[i].value;
				temp = i;
			}
		}
		//cout << temp + 1 << "  "<<min << endl;
		//把temp对应的顶点加入到已经找到的最短路径的集合中
		dis[temp].visit = true;
		++count;
		for (i = 0; i < this->vexnum; i++) {
			//注意这里的条件arc[temp][i]!=INT_MAX必须加，不然会出现溢出，从而造成程序异常
			if (!dis[i].visit && arc[temp][i] != INT_MAX && (dis[temp].value + arc[temp][i]) < dis[i].value) {
				//如果新得到的路径可以影响其他为访问的路由器，那就就更新它的最短路径和长度
				dis[i].value = dis[temp].value + arc[temp][i];
				dis[i].path = dis[temp].path + "-->v" + to_string(i + 1);
			}
		}
	}
}

void Graph_DG::print_path(int begin) {
	ofstream fout("1.txt");
	string str;
	str = "v" + to_string(begin);
	fout << "以" << str << "为起点的局域网的最短路径为：" << endl;
	for (int i = 0; i != this->vexnum; i++) {
		if (dis[i].value != INT_MAX)
			fout << dis[i].path << "=" << dis[i].value << endl;
		else {
			fout << dis[i].path << "是无最短路径的" << endl;
		}
	}
	fout.close();
}
void Graph_DG::delline() {
	cout << "输出删除路径两端的路由器序号";
	int m, n;
	cin >> m >> n;
	arc[m - 1][n - 1] = INT_MAX;
	arc[n - 1][m - 1] = INT_MAX;
}



void Graph_DG::delnode() {
	cout << "输入需删除路由器的序号:";
	int data;
	cin >> data;
	for (int i = 0; i < vexnum; i++) {
		arc[i][data - 1] = INT_MAX;
		arc[data - 1][i] = INT_MAX;
	}
}

void Graph_DG::addline() //增加某条路线
{
	cout << "输入需要增加路线两端的路由器序号及权重：";
	int m1, n1, q;
	cin >> m1 >> n1 >> q;
	for (int i = 0; i < vexnum; i++) {
		arc[m1 - 1][n1 - 1] = q;
		arc[n1 - 1][m1 - 1] = q;
	}
}

void Graph_DG::out_excel() //输出指定路由器的路由表
{
	ofstream fout("3.txt");
	fout << "目的网络号" << '\t' << "下一跳（路由器序号）" << endl;
	for (int i = 0; i < vexnum; i++) {
		if (dis[i].path.length() == 7)fout << i + 1 << ".x.x.x" << '\t' << '\t' << dis[i].path.at(6) << endl;
		if (dis[i].path.length() > 7) {
			if (dis[i].path.at(7) == '-')fout << i + 1 << ".x.x.x" << '\t' << '\t' << dis[i].path.at(6) << endl;
			else fout << i + 1 << ".x.x.x" << '\t' << '\t' << dis[i].path.at(6) << dis[i].path.at(7) << endl;
		}
		/*fout << i + 1 << ".x.x.x" << '\t' << '\t' << dis[i].path.at(6) << endl;*/
	}
}

bool check(int Vexnum, int edge) {
	if (Vexnum <= 0 || edge <= 0 || ((Vexnum * (Vexnum - 1)) / 2) < edge)
		return false;
	return true;
}

void Graph_DG::addnode() {
	vexnum++;
	cout << "输入新增的路径数目:";
	int numb;
	cin >> numb;
	cout << "与该路由器相连的其他路由器序号及权值（两路由器之间距离）为:";
	for (int i = 0; i < numb; i++) {
		int m, n;//m为其他路由器号,n为权值
		cin >> m >> n;
		arc[vexnum - 1][m] = n;
		arc[m][vexnum - 1] = n;
	}

}