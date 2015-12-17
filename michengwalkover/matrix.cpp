#include <iostream>
using namespace std;
int BlockNum;	//���õ�ʯͷ���� 
int BlankNum=25;//��ʼ��empty���� 
string matrix[5][5];
int judgeSinglepoint(int i,int j);


void clearMartrix(){
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			matrix[i][j]="00";
		}
	}
}

void printMatrix(){
	int i,j;
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			cout<<" "<<matrix[i][j];
		}
		cout<<endl;
	}
}

/*������������������ķ�����������в��� 
direction:
1-���ϲ��� 
2-���Ҳ��� 
3-���²��� 
4-������� 
*/
void eraser (int direction,int stepnum,int row,int column)
{
	int i=row,j=column;
	switch (direction){
	    case 1:
	    	while(stepnum>0){
	    		stepnum--;
	    		BlankNum++;
	    		matrix[i--][j]="00";
	    		printMatrix();
	    	}
	    case 2:
	    	while(stepnum>0){
	    		stepnum--;
	    		BlankNum++;
	    		matrix[i][j++]="00";
	    		printMatrix();
	    	}
	    case 3:
	    	while(stepnum>0){
	    		stepnum--;
	    		BlankNum++;
	    		matrix[i++][j]="00";
	    		printMatrix();
	    	}
	    case 4:
	    	while(stepnum>0){
	    		stepnum--;
	    		BlankNum++;
	    		matrix[i][j--]="00";
	    		printMatrix();
	    	}
	    default:
	    	return ;
	}
	return ;
}
void setBlock(){
	int rowValue,columnValue;
	cout<<"input block num:";
	cin>>BlockNum;
	BlankNum-=BlockNum;
	int count=BlockNum;
	while(count-->0){
		cout<<"set rowValue and columnValue:";
		cin>>rowValue>>columnValue;
		matrix[rowValue-1][columnValue-1]="xx";
	}
}
//����Ϊ�ĸ����ߺ���������·���Ĳ���ȫ����walk�����н��С� ����judgeSinglepoint�н��в���������̫�ҡ� 
int walkup(int i,int j){
	int res=0;
	int stepnum=0; 
	//����Ϸ�Խ������з�empty״̬�ĸ��ӣ���˵���Ϸ���·��ͨ������-1��
	if((i-1<0)||matrix[i-1][j]!="00") {
		return -1;
	}
	//����Ϸ���empty״̬�ĸ��ӣ���ʵ��ִ�����߲���
	//1��������ķ���״̬����Ϊ ��
	matrix[i][j]="��" ; 
	//2��������Խ���������empty״̬����Ϊֹ
	while(i-1>=0&&matrix[i-1][j]=="00"){
		i--;
		stepnum++;
		BlankNum--;
		matrix[i][j]="��" ; 
		cout<<"========================"<<endl;
		printMatrix();
	}
	res=judgeSinglepoint(i,j);
	//���Ϊ���ӣ�����в��������� 
	if(res==-1){
		eraser (3,stepnum, i, j); 
	}
	return res;
}

int walkright(int i,int j){
	int res=0;
	int stepnum=0; 
	//����ҷ�Խ������з�empty״̬�ĸ��ӣ���˵���ҷ���·��ͨ������-1��
	if((j+1>4)||matrix[i][j+1]!="00") {
		return -1;
	}
	//����ҷ���empty״̬�ĸ��ӣ���ʵ��ִ�����߲���
	//1��������ķ���״̬����Ϊ ��
	matrix[i][j]="��" ; 
	//2��������Խ���������empty״̬����Ϊֹ
	while(j+1<=4&&matrix[i][j+1]=="00"){
		j++;
		stepnum++;
		BlankNum--;
		matrix[i][j]="��" ; 
		cout<<"========================"<<endl;
		printMatrix();
	}
	res=judgeSinglepoint(i,j);
	//���Ϊ���ӣ�����в��������� 
	if(res==-1){
		eraser (4,stepnum, i, j); 
	}
	return res;
}
int walkdown(int i,int j){
	int res=0;
	int stepnum=0; 
	//����·�Խ������з�empty״̬�ĸ��ӣ���˵���·���·��ͨ������-1��
	if((i+1>4)||matrix[i+1][j]!="00") {
		return -1;
	}
	//����·���empty״̬�ĸ��ӣ���ʵ��ִ�����߲���
	//1��������ķ���״̬����Ϊ ��
	//���Ϊ��ʼ�㡣��Ϊ"st" ,���������Ϊԭ����
	matrix[i][j]="��" ; 
	//2��������Խ���������empty״̬����Ϊֹ
	while(i+1<=4&&matrix[i+1][j]=="00"){
		i++;
		stepnum++;
		BlankNum--;
		matrix[i][j]="��" ; 
		cout<<"========================"<<endl;
		printMatrix();
	}
	res=judgeSinglepoint(i,j);
	//���Ϊ���ӣ�����в��������� 
	if(res==-1){
		eraser (1,stepnum, i, j); 
	}
	return res;
}
int walkleft(int i,int j){
	int res=0;
	int stepnum=0; 
	//�����Խ������з�empty״̬�ĸ��ӣ���˵������·��ͨ������-1��
	if((j-1<0)||matrix[i][j-1]!="00") {
		return -1;
	}
	//�������empty״̬�ĸ��ӣ���ʵ��ִ�����߲���
	//1��������ķ���״̬����Ϊ ��
	matrix[i][j]="��" ; 
	//2��������Խ���������empty״̬����Ϊֹ
	while(j-1>=0&&matrix[i][j-1]=="00"){
		j--;
		stepnum++;
		BlankNum--;
		matrix[i][j]="��" ; 
		cout<<"========================"<<endl;
		printMatrix();
	}
	res=judgeSinglepoint(i,j);
	//���Ϊ���ӣ�����в���������
	if(res==-1){
		eraser (2,stepnum, i, j); 
	}
	return res;
}
/*״̬����
* x----------block
* ��������---pass
* 0----------empty
*/ 
int judgeSinglepoint(int i,int j){
	//*���ж��Ƿ񻹴���empty�ĸ���,��������ڣ�˵��ȫ���������ҵ����ʵ�·���� 
	if(BlankNum==0){
		return 0;
	}
	//������
	int up=walkup(i,j);
	if(up==0){
		return 0;
	}
	//������
	int right=walkright(i,j);
	if(right==0){
		return 0;
	}
	//������
	int down=walkdown(i,j);
	if(down==0){
		return 0;
	}
	//������
	int left=walkleft(i,j);
	if(left==0){
		return 0;
	}
	//���ȫ��������ͨ��˵��������ͨ������-1�� 
	if(up&&right&&down&&left){
		return -1;
	}

}
//��ʼʱ����жϣ�������ʱ���ʣ���Լ�δ���������������-1��֤����·��ͨ�����Լ���������i,j��λ��Ϊ00 
int judgeStartpoint(int i,int j){
	//��������ʼ��ҲҪ�۳��հ׸���Ŀ�����Թ����з��֣�����
	BlankNum--;
	int ret=judgeSinglepoint(i,j);
	if(ret==0){
		cout<<"xxxxxxxxxxxxxxxxxxxx"<<endl; 
		printMatrix();
	}
	else{
		matrix[i][j]="00";
		return -1;
	}
	return 0;
}



int main()
{
	int i,j;
	//clear matrix num
	clearMartrix();
	//clear matrix num
	printMatrix();
	//set block
	setBlock();
	cout<<"=================="<<endl;
	printMatrix();
	//ѭ���ж�start���Ƿ�����γ������պ� 
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			//�������Ϊempty,��ִ�п������ж�
			if(matrix[i][j]=="00"){
				if(!judgeStartpoint(i,j))
				{
					cout<<"find a way to walk over!"<<endl;
					if(matrix[i][j]=="��"){
						matrix[i][j]="up";
					}
					else if(matrix[i][j]=="��"){
						matrix[i][j]="rt";
					}
					else if(matrix[i][j]=="��"){
						matrix[i][j]="dn";
					}
					else if(matrix[i][j]=="��"){
						matrix[i][j]="lt";
					}
					printMatrix();
					return 0;
				}
			}
		}
	}
	return 0;
}
