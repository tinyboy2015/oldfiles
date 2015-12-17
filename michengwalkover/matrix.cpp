#include <iostream>
using namespace std;
int BlockNum;	//设置的石头数量 
int BlankNum=25;//初始的empty数量 
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

/*擦除函数，传入擦除的方向和数量进行擦除 
direction:
1-向上擦除 
2-向右擦除 
3-向下擦除 
4-向左擦除 
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
//如下为四个行走函数，已走路径的擦除全部在walk函数中进行。 不在judgeSinglepoint中进行擦除。否则太乱。 
int walkup(int i,int j){
	int res=0;
	int stepnum=0; 
	//如果上方越界或者有非empty状态的格子，则说明上方死路不通，返回-1；
	if((i-1<0)||matrix[i-1][j]!="00") {
		return -1;
	}
	//如果上方有empty状态的格子，则实际执行上走操作
	//1、将自身的方向状态更改为 ↑
	matrix[i][j]="↑" ; 
	//2、上走至越界或碰到非empty状态格子为止
	while(i-1>=0&&matrix[i-1][j]=="00"){
		i--;
		stepnum++;
		BlankNum--;
		matrix[i][j]="↑" ; 
		cout<<"========================"<<endl;
		printMatrix();
	}
	res=judgeSinglepoint(i,j);
	//如果为死子，则进行擦除操作。 
	if(res==-1){
		eraser (3,stepnum, i, j); 
	}
	return res;
}

int walkright(int i,int j){
	int res=0;
	int stepnum=0; 
	//如果右方越界或者有非empty状态的格子，则说明右方死路不通，返回-1；
	if((j+1>4)||matrix[i][j+1]!="00") {
		return -1;
	}
	//如果右方有empty状态的格子，则实际执行右走操作
	//1、将自身的方向状态更改为 →
	matrix[i][j]="→" ; 
	//2、右走至越界或碰到非empty状态格子为止
	while(j+1<=4&&matrix[i][j+1]=="00"){
		j++;
		stepnum++;
		BlankNum--;
		matrix[i][j]="→" ; 
		cout<<"========================"<<endl;
		printMatrix();
	}
	res=judgeSinglepoint(i,j);
	//如果为死子，则进行擦除操作。 
	if(res==-1){
		eraser (4,stepnum, i, j); 
	}
	return res;
}
int walkdown(int i,int j){
	int res=0;
	int stepnum=0; 
	//如果下方越界或者有非empty状态的格子，则说明下方死路不通，返回-1；
	if((i+1>4)||matrix[i+1][j]!="00") {
		return -1;
	}
	//如果下方有empty状态的格子，则实际执行下走操作
	//1、将自身的方向状态更改为 ↑
	//如果为起始点。置为"st" ,其它情况置为原方向。
	matrix[i][j]="↓" ; 
	//2、下走至越界或碰到非empty状态格子为止
	while(i+1<=4&&matrix[i+1][j]=="00"){
		i++;
		stepnum++;
		BlankNum--;
		matrix[i][j]="↓" ; 
		cout<<"========================"<<endl;
		printMatrix();
	}
	res=judgeSinglepoint(i,j);
	//如果为死子，则进行擦除操作。 
	if(res==-1){
		eraser (1,stepnum, i, j); 
	}
	return res;
}
int walkleft(int i,int j){
	int res=0;
	int stepnum=0; 
	//如果左方越界或者有非empty状态的格子，则说明左方死路不通，返回-1；
	if((j-1<0)||matrix[i][j-1]!="00") {
		return -1;
	}
	//如果左方有empty状态的格子，则实际执行上走操作
	//1、将自身的方向状态更改为 ↑
	matrix[i][j]="←" ; 
	//2、上走至越界或碰到非empty状态格子为止
	while(j-1>=0&&matrix[i][j-1]=="00"){
		j--;
		stepnum++;
		BlankNum--;
		matrix[i][j]="←" ; 
		cout<<"========================"<<endl;
		printMatrix();
	}
	res=judgeSinglepoint(i,j);
	//如果为死子，则进行擦除操作。
	if(res==-1){
		eraser (2,stepnum, i, j); 
	}
	return res;
}
/*状态种类
* x----------block
* ←↑→↓---pass
* 0----------empty
*/ 
int judgeSinglepoint(int i,int j){
	//*先判断是否还存在empty的格子,如果不存在，说明全部遍历，找到合适的路径。 
	if(BlankNum==0){
		return 0;
	}
	//向上走
	int up=walkup(i,j);
	if(up==0){
		return 0;
	}
	//向右走
	int right=walkright(i,j);
	if(right==0){
		return 0;
	}
	//向下走
	int down=walkdown(i,j);
	if(down==0){
		return 0;
	}
	//向左走
	int left=walkleft(i,j);
	if(left==0){
		return 0;
	}
	//如果全部不能走通，说明不能走通，返回-1。 
	if(up&&right&&down&&left){
		return -1;
	}

}
//起始时点的判断，擦除的时候会剩下自己未被擦除。如果返回-1，证明此路不通，将自己擦除，即i,j点位置为00 
int judgeStartpoint(int i,int j){
	//忽略了起始点也要扣除空白格数目，调试过程中发现，补上
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
	//循环判断start点是否可以形成完整闭合 
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			//如果自身为empty,则执行可行性判断
			if(matrix[i][j]=="00"){
				if(!judgeStartpoint(i,j))
				{
					cout<<"find a way to walk over!"<<endl;
					if(matrix[i][j]=="↑"){
						matrix[i][j]="up";
					}
					else if(matrix[i][j]=="→"){
						matrix[i][j]="rt";
					}
					else if(matrix[i][j]=="↓"){
						matrix[i][j]="dn";
					}
					else if(matrix[i][j]=="←"){
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
