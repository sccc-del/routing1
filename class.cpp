#include"class.h"
#include<fstream>
Graph_DG::Graph_DG(int vexnum, int edge) {
	//��ʼ��·��������·����
	this->vexnum = vexnum;
	this->edge = edge;
	//Ϊ�ڽӾ��󿪱ٿռ�͸���ֵ

	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			arc[i][j] = INT_MAX;
		}
		dis[i].path = "";
		dis[i].value = INT_MAX;
		dis[i].visit = true;
	}

}

//��������
Graph_DG::~Graph_DG() {
	delete[] dis;
	for (int i = 0; i < this->vexnum; i++) {
		delete this->arc[i];
	}
	delete arc;
}

// �ж�����ÿ������ĵ�·������Ϣ�Ƿ�Ϸ�
//·������1��ʼ���
bool Graph_DG::check_edge_value(int start, int end, int weight) {
	if (start<1 || end<1 || start>vexnum || end>vexnum || weight < 0) {
		return false;
	}
	return true;
}

void Graph_DG::createGraph() {
	cout << "������ÿ��·���������յ㣨·������Ŵ�1��ʼ���Լ���Ȩ��" << endl;
	int start;
	int end;
	int weight;
	int count = 0;
	while (count != this->edge) {
		cin >> start >> end >> weight;
		//�����ж�·������Ϣ�Ƿ�Ϸ�
		while (!this->check_edge_value(start, end, weight)) {
			cout << "�����·������Ϣ���Ϸ�������������" << endl;
			cin >> start >> end >> weight;
		}
		//���ڽӾ����Ӧ�ϵ�·������ֵ
		arc[start - 1][end - 1] = weight;
		//����������ͼ����ȫ����
		arc[end - 1][start - 1] = weight;
		++count;
	}
}

void Graph_DG::print() {
	cout << "������ͼ���ڽӾ���Ϊ��" << endl;
	int count_row = 0; //��ӡ�еı�ǩ
	int count_col = 0; //��ӡ�еı�ǩ
	//��ʼ��ӡ
	while (count_row != this->vexnum) {
		count_col = 0;
		while (count_col != this->vexnum) {
			if (arc[count_row][count_col] == INT_MAX)
				cout << "��" << " ";
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
		//���õ�ǰ��·��
		dis[i].path = "v" + to_string(begin) + "-->v" + to_string(i + 1);
		dis[i].value = arc[begin - 1][i];
		dis[i].visit = false;
	}
	//�������·�����ĵ�ĩ��·������·��Ϊ0
	dis[begin - 1].value = 0;
	dis[begin - 1].visit = true;
}



void Graph_DG::Dijkstra() {
	int i;
	int count = 1;
	//����ʣ���·���������·����ʣ��this->vexnum-1�����㣩
	while (count != this->vexnum) {
		//temp���ڱ��浱ǰdis��������С���Ǹ��±�
		//min��¼�ĵ�ǰ����Сֵ
		int temp = 0;
		int min = INT_MAX;
		for (i = 0; i < this->vexnum; i++) {
			if (!dis[i].visit && dis[i].value < min) {
				min = dis[i].value;
				temp = i;
			}
		}
		//cout << temp + 1 << "  "<<min << endl;
		//��temp��Ӧ�Ķ�����뵽�Ѿ��ҵ������·���ļ�����
		dis[temp].visit = true;
		++count;
		for (i = 0; i < this->vexnum; i++) {
			//ע�����������arc[temp][i]!=INT_MAX����ӣ���Ȼ�����������Ӷ���ɳ����쳣
			if (!dis[i].visit && arc[temp][i] != INT_MAX && (dis[temp].value + arc[temp][i]) < dis[i].value) {
				//����µõ���·������Ӱ������Ϊ���ʵ�·�������Ǿ;͸����������·���ͳ���
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
	fout << "��" << str << "Ϊ���ľ����������·��Ϊ��" << endl;
	for (int i = 0; i != this->vexnum; i++) {
		if (dis[i].value != INT_MAX)
			fout << dis[i].path << "=" << dis[i].value << endl;
		else {
			fout << dis[i].path << "�������·����" << endl;
		}
	}
	fout.close();
}
void Graph_DG::delline() {
	cout << "���ɾ��·�����˵�·�������";
	int m, n;
	cin >> m >> n;
	arc[m - 1][n - 1] = INT_MAX;
	arc[n - 1][m - 1] = INT_MAX;
}



void Graph_DG::delnode() {
	cout << "������ɾ��·���������:";
	int data;
	cin >> data;
	for (int i = 0; i < vexnum; i++) {
		arc[i][data - 1] = INT_MAX;
		arc[data - 1][i] = INT_MAX;
	}
}

void Graph_DG::addline() //����ĳ��·��
{
	cout << "������Ҫ����·�����˵�·������ż�Ȩ�أ�";
	int m1, n1, q;
	cin >> m1 >> n1 >> q;
	for (int i = 0; i < vexnum; i++) {
		arc[m1 - 1][n1 - 1] = q;
		arc[n1 - 1][m1 - 1] = q;
	}
}

void Graph_DG::out_excel() //���ָ��·������·�ɱ�
{
	ofstream fout("3.txt");
	fout << "Ŀ�������" << '\t' << "��һ����·������ţ�" << endl;
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
	cout << "����������·����Ŀ:";
	int numb;
	cin >> numb;
	cout << "���·��������������·������ż�Ȩֵ����·����֮����룩Ϊ:";
	for (int i = 0; i < numb; i++) {
		int m, n;//mΪ����·������,nΪȨֵ
		cin >> m >> n;
		arc[vexnum - 1][m] = n;
		arc[m][vexnum - 1] = n;
	}

}