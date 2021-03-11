/***********************************
 * Name & Surname: Jilan Alrehaili
 * Student Number: 150160922
************************************
*/
#include <cstdlib>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <limits>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#define INFINTY 9999

using namespace std;

string fileName;
int numOfNodes;
int graph[100][100];
int source,target; 					  //used in dijkstra method
int source1,target1,source2,target2; //variables from input file
int total; 							 //total duration time
int path[100][3],path2[100][3];		
int timer;
bool second;						//second is to check if its in second path=path2 or first path
            
//............ Construct all values of graph from input file ............//
void constructGraph(){ 
	ifstream input_file;
	input_file.open(fileName.c_str()); 

	int elem1,elem2,elem3,elem4;
	int counter=1;
	char x1,x2;

	while (!input_file.eof()){	 		   			//start reading file

		if(counter==1){		     		   			//first line of file has number of nodes 
		input_file >> numOfNodes ;
		
		for(int i=0; i<numOfNodes; i++)   		   //construct graph as given number of nodes 
			for(int j=0; j<numOfNodes; j++)
			{
				if(i==j){
					graph[i][j]=0;
					}
				else{
					graph[i][j]=INFINTY;
				}
			}
		}
		else if(counter==2){		  				//second line has source/target values
			input_file >> elem1 >> elem2 >> elem3 >> elem4 ;
			source=elem1;  
			source1=elem1;
			
			target=elem2;  
			target1=elem2;
			
			source2=elem3;
			target2=elem4;
		}

		else{
			input_file >> elem1 >> elem2 >> elem3; //the next lines has the edges of graph information
			graph[elem1][elem2]=elem3;
		}
		counter++;
	}
}  
//............ Find vertix with minimum distance value ............//
int minDistance(int dist[], int visited[])
{ 
    int val = INFINTY;
    int minVal;
    for(int v = 0; v < numOfNodes; v++)
    {           
        if((val > dist[v])&& (visited[v] == 0)) {
			val = dist[v]; 
			minVal = v; 
			}        
    }
    return minVal;    
}
//............  Dijkstra algorithm to find the shortest path for a graph source->target ............//
int dijkstra()
{		
   int dist[numOfNodes];
   int prev[numOfNodes];
   int arr[numOfNodes];
   int visited[numOfNodes];

     dist[source] = 0;  //distance of itself is zero
     prev[source] = -1; //previous node is -1
     
     for(int i = 0; i < numOfNodes; i++)
     {
       if(i != source)
       {
            dist[i] = INFINTY; 
            prev[i] = -1;
       }
       arr[i] = i;
       visited[i] = 0;  //initially all nodes are not visited so its zero
     }
     int  u,tmp;
     u = arr[source];   //u is initially the source value and it is visited 
     visited[u] = 1;
     int privous=-1;
     bool err=false;
     while (visited[target] == 0) //loop until the target is visited
     {
           for(int i = 0; i < numOfNodes; i++)
           {           
               tmp = dist[u] + graph[u][i];
               if((tmp < dist[i]) && (visited[i] == 0))
               {
                      dist[i] = tmp;
                      prev[i] = u;       
               }        
           }
           privous=u;
           u = arr[minDistance(dist,visited)]; //set u as minimum distince vertix 
           visited[u] = 1;
           if(privous==u){  //if the privous is equal to current there is an error
				err=true;
				break;
			}
           
     }
     if(err==true)
		return 0;
     
     int x = 0;
     int array[numOfNodes];
     u = target;
     int enter=0;	
     while(prev[u] != -1) //traversing the shortest path 
     {
         array[x++] = u; 
         u = prev[u];  	
         enter++; 
     }
     if(enter==0)		//enter will check if it entered the traverse, if not then there's no path=error stop
		return 0;
     
    total=dist[target];
    if(second==false){ 
		path[0][0]=source; path[0][1]=array[x-1]; path[0][2]=graph[source][array[x-1]];
	}
	if(second==true){ 
		path2[0][0]=source; path2[0][1]=array[x-1]; path2[0][2]=graph[source][array[x-1]];
	}
			
    int c=1;
	for(int i = x-1; i > 0; i--) {
		if(second==false){
			path[c][0]=array[i]; path[c][1]=array[i-1]; path[c][2]=graph[array[i]][array[i-1]];
		}
		if(second==true){
			path2[c][0]=array[i]; path2[c][1]=array[i-1]; path2[c][2]=graph[array[i]][array[i-1]];
		}
		c++;
	}
	
	timer=c;
	return 1; // no error path found return 1
     
} 
//............ Check if deleted path is accepted ............//
int checkPath(bool flag,int s,int t,int p1,int p2){
	second=flag;
	constructGraph(); 
	source=s; 	
	target=t;
	graph[p1][p2]=INFINTY; //delete this path  
	int result=dijkstra();
	constructGraph(); 		//return to its default construct
	return result;
}

//............ Start dijkstra and print results ............//
void doDijkstra(){ 
	
	/* First stage */
	second=false;
	int fs=dijkstra( );
    int total1=total; // first stage total duration
    int p1[100][3];
    int time1=timer;
    for(int i=0;i<timer;i++){
		if(i!=0){
			path[i][2]=path[i][2]+path[i-1][2];
			p1[i][0]=path[i][0];
			p1[i][1]=path[i][1];
			p1[i][2]=path[i][2];

		}
		else{
			path[i][2]=path[i][2];
			p1[i][0]=path[i][0];
			p1[i][1]=path[i][1];
			p1[i][2]=path[i][2];

		}
	}
	
	/* Second stage */	
	second=true;
	source=source2; //change from source1 to source2 for second stage
	target=target2;
    int ss=dijkstra( );
    int total2=total;
    int p2[100][3];
    int time2=timer;
    for(int i=0;i<timer;i++){
		if(i!=0){
			path2[i][2]=path2[i][2]+path2[i-1][2];
			p2[i][0]=path2[i][0];
			p2[i][1]=path2[i][1];
			p2[i][2]=path2[i][2];
		}
		else{
			path2[i][2]=path2[i][2];
			p2[i][0]=path2[i][0];
			p2[i][1]=path2[i][1];
			p2[i][2]=path2[i][2];
		}
	}
	//------Test if there is an internsection--------------------------------------------------------//
	bool stop=false;  //if stop is true it means there is an intersection point
	int p1_1,p1_2;
	int p2_1,p2_2;
	
    for(int i=0;i<100;i++){
		for(int j=0;j<100;j++){
			if(path[i][1]==path2[j][1] && (path[i][2]==path2[j][2]) && path[i][2]!=0){
				p1_1=path[i][0];   //first path intresection
				p1_2=path[i][1];
				
				p2_1=path2[j][0];  //second path intersection
				p2_2=path2[j][1];
				stop=true;
				break;}
				
				for(int k=1;k<=30;k++){   	//for case-4 as in dashboard
					if(path[i][1]==path2[j][1] && ((path[time1-1][2]+k)==path2[j][2]||path[i][2]==(path2[time2-1][2]+k))){
						p1_1=path[i][0];   //first path intresection
						p1_2=path[i][1];
						p2_1=path2[j][0];  //second path intersection
						p2_2=path2[j][1];
						stop=true;
						break;}
				}
		}
		if(stop==true)
		break;
	}
	bool first_stage=false; //whether to change the path of intersection
	bool second_stage=false;
	if(stop==true){ //if stop is true there is an intersection
		if(fs==1 && ss==1){//////////// -1 //////////////
			if(total2>total1){					
				int result=checkPath(true,target2,source2,p2_1,p2_2);
				if(result==1){				   //check if deleted path is okay
					second_stage=true;
				}
				else{
					result=checkPath(false,target1,source1,p1_1,p1_2);
					if(result==1)
						first_stage=true;	
					else{
							cout<<"Error! There is no solution"<<endl;
							return;
						}
				}
			}
			else if(total2<total1){
				int result=checkPath(false,target1,source1,p1_1,p1_2);
				if(result==1)				   
					first_stage=true;
				else{
					result=checkPath(true,target2,source2,p2_1,p2_2);
					if(result==1)
						second_stage=true;	
					else{
							cout<<"Error! There is no solution"<<endl;
							return;
						}
				}
			}
		}
		else { //////////// -2 //////////////
			if(fs==0 && ss==1){
				int result=checkPath(false,target1,source1,p1_1,p1_2);
				if(result==1)				  
					first_stage=true;
				else{
					cout<<"Error! There is no solution"<<endl;
					return;
				}
			}
			if(ss==0 && fs==1){
				int result=checkPath(true,target2,source2,p2_1,p2_2);
				if(result==1)				  
					second_stage=true;
				else{
					cout<<"Error! There is no solution"<<endl;
					return;
				}
			}
			else if (fs==0 && ss==0){
				cout<<"Error! There is no solution"<<endl;
				return;
			}
		}	
	}
    /* Third stage */
    source=target1; //source is equal to target because of return to distenation
    target=source1;
    second=false;
    int ts=dijkstra( );
    int total3=total;
    int time3=timer;
    for(int i=0;i<timer;i++){
		if(i!=0){
			path[i][2]=path[i][2]+path[i-1][2];

		}
		else{
			path[i][2]=path[i][2]+total1+30;

		}
	}
	/* Fourth stage */
	source=target2;
    target=source2;
    second=true;
    int frs=dijkstra( );
    int total4=total;
    int time4=timer;
    for(int i=0;i<timer;i++){
		if(i!=0){
			path2[i][2]=path2[i][2]+path2[i-1][2];
		}
		else{
			path2[i][2]=path2[i][2]+total2+30;
		}
	}
	
	//------Test if there is an internsection--------------------------------------------------------//

	stop=false;
	int p3_1,p3_2;
	int p4_1,p4_2;
    for(int i=0;i<100;i++){
		for(int j=0;j<100;j++){
			if(path[i][1]==path2[j][1] && (path[i][2]==path2[j][2]) && path[i][2]!=0){
				p3_1=path[i][0];
				p3_2=path[i][1];
				
				p4_1=path2[j][0];
				p4_2=path2[j][1];
				stop=true;
				break;}
			for(int k=1;k<=30;k++){   //for case-4 as in dashboard
				if((p2[time2-1][2]+k)==path[j][2]||(p1[time1-1][2]+k)==path2[j][2]){
					p3_1=path[i][0];
					p3_2=path[i][1];
					
					p4_1=path2[j][0];
					p4_2=path2[j][1];
					stop=true;
					break;}
				}

		}
		if(stop==true)
		break;
	}
	bool third_stage=false; 
	bool fourth_stage=false;
	if(stop==true){
		
		if(ts==1 && frs==1){//////////// -1 //////////////
			if(total3>total4){	
				int result=checkPath(false,target1,source1,p3_1,p3_2);
				if(result==1)				   //check if deleted path is okay
					third_stage=true;
				else{
					result=checkPath(true,target2,source2,p4_1,p4_2);
					if(result==1)
						fourth_stage=true;
					else{
						cout<<"Error! There is no solution"<<endl;
						return;
					}
				}
			}
			else if(total3<total4){
				int result=checkPath(true,target2,source2,p4_1,p4_2);
				if(result==1)				   
					fourth_stage=true;
				else{
					result=checkPath(false,target1,source1,p3_1,p3_2);
					if(result==1)
						third_stage=true;
					else{
						cout<<"Error! There is no solution"<<endl;
						return;
					}	
				}
			}
		}
		
		else { //////////// -2 //////////////
			if(ts==0 && frs==1){
				int result=checkPath(false,target1,source1,p3_1,p3_2);
				if(result==1)				  
					third_stage=true;
				else{
						cout<<"Error! There is no solution"<<endl;
						return;
					}
			}
			if(frs==0 && ts==1){
				int result=checkPath(true,target2,source2,p4_1,p4_2);
				if(result==1)				  
					fourth_stage=true;
				else{
						cout<<"Error! There is no solution"<<endl;
						return;
					}
			}
			else if (frs==0 && ts==0){
				cout<<"Error! There is no solution"<<endl;
				return;
			}
		}
					
	}
	//.................Last step configure & print..................//
	cout<<"\n>> Path from node "<<source1<<" to "<<target1<<" <<\n";
	if(first_stage==false){  //no change just print
		int i;
		for( i=0;i<time1;i++){
			cout<<"Node "<<p1[i][0]<<" to "<<p1[i][1]<<" Time: "<<p1[i][2]<<endl;
		}
		cout<<"(Node "<<p1[i-1][1]<<" wait: "<<p1[i-1][2]+30<<")\n";
	}
	else if(first_stage==true){ //we need to change path
		
		second=false;
		source=source1;
		target=target1;
		graph[p1_1][p1_2]=INFINTY; //delete this path  
		fs=dijkstra();
		total1=total;
		int i;
		for( i=0;i<timer;i++){
			if(i!=0){
				path[i][2]=path[i][2]+path[i-1][2];
			}
			else{
				path[i][2]=path[i][2];
			}
			cout<<"Node "<<path[i][0]<<" to "<<path[i][1]<<" Time: "<<path[i][2]<<endl;
		}	
		cout<<"(Node "<<path[i-1][1]<<" wait: "<<path[i-1][2]+30<<")\n";
	}
	cout<<"---- return ----\n";
	if(third_stage==false){
	constructGraph();
    source=target1;
    target=source1;
    second=false;
    ts=dijkstra( );
    total3=total;
    time3=timer;
    for(int i=0;i<timer;i++){
		if(i!=0){
			path[i][2]=path[i][2]+path[i-1][2];
		}
		else{
			path[i][2]=path[i][2]+total1+30;
		}
	}
		int i;
		for(i=0;i<time3;i++){
			cout<<"Node "<<path[i][0]<<" to "<<path[i][1]<<" Time: "<<path[i][2]<<endl;
		}
		cout<<"Total duration time is: "<<path[i-1][2]<<endl;
	}
	else if(third_stage==true){
		second=false; 
		constructGraph();
		source=target1;
		target=source1;
		graph[p3_1][p3_2]=INFINTY; //delete this path  
		ts=dijkstra();
		int i;
		for(i=0;i<timer;i++){
			if(i!=0){
				path[i][2]=path[i][2]+path[i-1][2];
			}
			else{
				path[i][2]=path[i][2]+p1[time1-1][2]+30;
			}
			cout<<"Node "<<path[i][0]<<" to "<<path[i][1]<<" Time: "<<path[i][2]<<endl;
		}
		cout<<"Total duration time is: "<<path[i-1][2]<<endl;	
	}
	
	cout<<"\n>> Path from node "<<source2<<" to "<<target2<<" <<\n";
	if(second_stage==false){
		int i;
		for(i=0;i<time2;i++){
			cout<<"Node "<<p2[i][0]<<" to "<<p2[i][1]<<" Time: "<<p2[i][2]<<endl;
		}
		cout<<"(Node "<<p2[i-1][1]<<" wait: "<<p2[i-1][2]+30<<")\n";
	}
	else if(second_stage==true){
		second=true; 
		constructGraph();
		source=source2;
		target=target2;
		graph[p2_1][p2_2]=INFINTY; //delete this path  
		ss=dijkstra();
		total2=total;
		int i;
		for(i=0;i<timer;i++){
			if(i!=0){
				path2[i][2]=path2[i][2]+path2[i-1][2];
			}
			else{
				path2[i][2]=path2[i][2];
			}
			cout<<"Node "<<path2[i][0]<<" to "<<path2[i][1]<<" Time: "<<path2[i][2]<<endl;
		}cout<<"(Node "<<path2[i-1][1]<<" wait: "<<path2[i-1][2]+30<<")\n";
	}
	cout<<"---- return ----\n";
	if(fourth_stage==false){
	constructGraph();
    source=target2;
    target=source2;
    second=true;
    frs=dijkstra( );
    total4=total;
    time4=timer;
    for(int i=0;i<timer;i++){
		if(i!=0){
			path2[i][2]=path2[i][2]+path2[i-1][2];
		}
		else{
			path2[i][2]=path2[i][2]+total2+30;
		}
	}
		int i;
		for(i=0;i<time4;i++){
			cout<<"Node "<<path2[i][0]<<" to "<<path2[i][1]<<" Time: "<<path2[i][2]<<endl;
		}
		cout<<"Total duration time is: "<<path2[i-1][2]<<endl;
	
	}
	else if(fourth_stage==true){
		second=true;
		constructGraph(); 
		source=target2;
		target=source2;
		graph[p4_1][p4_2]=INFINTY; //delete this path  
		frs=dijkstra();
		int i;
		for(i=0;i<timer;i++){
			if(i!=0){
				path2[i][2]=path2[i][2]+path2[i-1][2];
			}
			else{
				path2[i][2]=path2[i][2]+p2[time2-1][2]+30;
			}
			cout<<"Node "<<path2[i][0]<<" to "<<path2[i][1]<<" Time: "<<path2[i][2]<<endl;
		}
		cout<<"Total duration time is: "<<path2[i-1][2]<<endl;
	}
}

int main(int argc,  const char * argv[])
{	
	string input=argv[1];
	fileName=input.c_str();
	constructGraph();  //file name as a command line argument
	doDijkstra();	  //start Dijkstra to the graph and print result
				
    return 0;
}
