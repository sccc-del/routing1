#include"class.h"

int main() {
	int vexnum; int edge;
	cout << "���������ͼ��·����������·����������" << endl;
	cin >> vexnum >> edge;
	while (!check(vexnum, edge)) {
		cout << "�������ֵ���Ϸ�������������" << endl;
		cin >> vexnum >> edge;
	}
	Graph_DG graph(vexnum, edge);
	graph.createGraph();
	while (1) {
		cout << "ʵ�ֹ������£�" << endl;
		cout << "1.��ӡ�ڽӾ���" << endl;
		cout << "2.ѡ��·���������·�ɱ�" << endl;
		cout << "3.ɾ��ĳһ��·�ߣ������·�ߵ�ʼĩ·����ţ�" << endl;
		cout << "4.ɾ��ĳһ·�����������·������ţ�" << endl;
		cout << "5.����ĳһ��·�ߣ������·�ߵ�ʼĩ·����ţ�" << endl;
		cout << "6.����ĳһ·�����������·������ţ�" << endl;
		int m;
		cin >> m;
		if (m == 1)graph.print();
		else if (m == 2) {
			int begin;
			cin >> begin;
			graph.work_begin(begin);
			graph.Dijkstra();
			graph.out_excel();
			graph.print_path(begin);
		}
		else if (m == 3)
		{
			graph.delline();
			int begin;
			cin >> begin;
			graph.work_begin(begin);
			graph.Dijkstra();
			graph.out_excel();
			graph.print_path(begin);
		}
		else if (m == 4)
		{
			graph.delnode();
			int begin;
			cin >> begin;
			graph.work_begin(begin);
			graph.Dijkstra();
			graph.out_excel();
			graph.print_path(begin);
		}
		else if (m == 5) {
			graph.addline();
			int begin;
			cin >> begin;
			graph.work_begin(begin);
			graph.Dijkstra();
			graph.out_excel();
			graph.print_path(begin);
		}
		else if (m == 6) {
			graph.addnode();
			int begin;
			cin >> begin;
			graph.work_begin(begin);
			graph.Dijkstra();
			graph.out_excel();
			graph.print_path(begin);
		}
		else break;

	}
	return 0;
}
