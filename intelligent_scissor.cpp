// intelligent_scissor.cpp : Defines the entry point for the console application.
//
#include "StdAfx.h"
#include <iostream>
#include <cmath>
#include "node.h"

//#include "fibheap.cpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;
FibHeap myheap;
Size size;
Mat imgf,imgb,img,imginit,costgraph,imgpathtree,imgpathtree2,imgpn,imgmask;
int mode=0;
int cursorx,cursory,seedx,seedy;
double statecount=0;
Node** Array=NULL;
int poi=0;

void ShortestPath(int yf,int xf){
	Array[xf][yf].totalCost=0;
	Array[xf][yf].state=1;
	statecount++;
	Array[xf][yf].prevNode=NULL;
	int xs,ys;
	myheap.Insert(&Array[xf][yf]);
	while(myheap.GetNumNodes()>0){
		FibHeapNode* thisnode=new FibHeapNode();
		thisnode=myheap.ExtractMin();
		xs=thisnode->row;
		ys=thisnode->column;
		Array[xs][ys].state=2;
		if(Array[xs-1][ys-1].totalCost>Array[xs][ys].totalCost+Array[xs][ys].linkCost[3]){
		Node* y=new Node();
		*y=Array[xs-1][ys-1];
		Array[xs-1][ys-1].totalCost=Array[xs][ys].totalCost+Array[xs][ys].linkCost[3];
		Array[xs-1][ys-1].prevNode=&Array[xs][ys];
		if(Array[xs-1][ys-1].state==0){
		if (xs>1&&xs<size.height-2&&ys>1&&ys<size.width-2){
			myheap.Insert(&Array[xs-1][ys-1]);
			Array[xs-1][ys-1].state=1;
			statecount++;
		}
		}
		else if(Array[xs-1][ys-1].state==1){
			Node* x=new Node();
			*x=Array[xs-1][ys-1];
			myheap.DecreaseKey(&Array[xs-1][ys-1],*x);
		}
	}
	if(Array[xs][ys-1].totalCost>Array[xs][ys].totalCost+Array[xs][ys].linkCost[2]){
		Node* y=new Node();
		*y=Array[xs][ys-1];
		Array[xs][ys-1].totalCost=Array[xs][ys].totalCost+Array[xs][ys].linkCost[2];
		Array[xs][ys-1].prevNode=&Array[xs][ys];
		if(Array[xs][ys-1].state==0){
		if (xs>1&&xs<size.height-2&&ys>1&&ys<size.width-2){
	//		Node* x=new Node();
	//		*x=Array[xs][ys-1];
			myheap.Insert(&Array[xs][ys-1]);
			Array[xs][ys-1].state=1;
			statecount++;
		}
		}
		else if(Array[xs][ys-1].state==1){
			Node* x=new Node();
			*x=Array[xs][ys-1];
			myheap.DecreaseKey(&Array[xs][ys-1],*x);}
	}
	
	if(Array[xs+1][ys-1].totalCost>Array[xs][ys].totalCost+Array[xs][ys].linkCost[1]){
		Node* y=new Node();
		*y=Array[xs+1][ys-1];
		Array[xs+1][ys-1].totalCost=Array[xs][ys].totalCost+Array[xs][ys].linkCost[1];
		Array[xs+1][ys-1].prevNode=&Array[xs][ys];
		if(Array[xs+1][ys-1].state==0){
		if (xs>1&&xs<size.height-2&&ys>1&&ys<size.width-2){
	//		Node* x=new Node();
	//		*x=Array[xs+1][ys-1];
			myheap.Insert(&Array[xs+1][ys-1]);
			Array[xs+1][ys-1].state=1;
			statecount++;
		}
		}
		else if(Array[xs+1][ys-1].state==1){
			Node* x=new Node();
			*x=Array[xs+1][ys-1];
			myheap.DecreaseKey(&Array[xs+1][ys-1],*x);
			
		}
	}
		if(Array[xs-1][ys].totalCost>Array[xs][ys].totalCost+Array[xs][ys].linkCost[4]){
		Node* y=new Node();
		*y=Array[xs-1][ys];
		Array[xs-1][ys].totalCost=Array[xs][ys].totalCost+Array[xs][ys].linkCost[4];
		Array[xs-1][ys].prevNode=&Array[xs][ys];
		if(Array[xs-1][ys].state==0){
		if (xs>1&&xs<size.height-2&&ys>1&&ys<size.width-2){
	//		Node* x=new Node();
		//	*x=Array[xs-1][ys];
			myheap.Insert(&Array[xs-1][ys]);
			Array[xs-1][ys].state=1;
			statecount++;
		}
		}
		else if(Array[xs-1][ys].state==1){
			Node* x=new Node();
			*x=Array[xs-1][ys];
			myheap.DecreaseKey(&Array[xs-1][ys],*x);}
	}
	
	if(Array[xs+1][ys].totalCost>Array[xs][ys].totalCost+Array[xs][ys].linkCost[0]){
		Node* y=new Node();
		*y=Array[xs+1][ys];
		Array[xs+1][ys].totalCost=Array[xs][ys].totalCost+Array[xs][ys].linkCost[0];
		Array[xs+1][ys].prevNode=&Array[xs][ys];
		if(Array[xs+1][ys].state==0){
		if (xs>1&&xs<size.height-2&&ys>1&&ys<size.width-2){
	//		Node* x=new Node();
		//	*x=Array[xs+1][ys];
			myheap.Insert(&Array[xs+1][ys]);
			Array[xs+1][ys].state=1;
			statecount++;
		}
		}
		else if(Array[xs+1][ys].state==1){
			Node* x=new Node();
			*x=Array[xs+1][ys];
			myheap.DecreaseKey(&Array[xs+1][ys],*x);}
	
	}
	if(Array[xs-1][ys+1].totalCost>Array[xs][ys].totalCost+Array[xs][ys].linkCost[5]){
		Node* y=new Node();
		*y=Array[xs-1][ys+1];
		Array[xs-1][ys+1].totalCost=Array[xs][ys].totalCost+Array[xs][ys].linkCost[5];
		Array[xs-1][ys+1].prevNode=&Array[xs][ys];
		if(Array[xs-1][ys+1].state==0){
		if (xs>1&&xs<size.height-2&&ys>1&&ys<size.width-2){
	//		Node* x=new Node();
	//		*x=Array[xs-1][ys+1];
			myheap.Insert(&Array[xs-1][ys+1]);
			Array[xs-1][ys+1].state=1;
			statecount++;
		}
		}
		else if(Array[xs-1][ys+1].state==1){
			Node* x=new Node();
			*x=Array[xs-1][ys+1];
			myheap.DecreaseKey(&Array[xs-1][ys+1],*x);
		}
	
	}
	if(Array[xs][ys+1].totalCost>Array[xs][ys].totalCost+Array[xs][ys].linkCost[6]){
		Node* y=new Node();
		*y=Array[xs][ys+1];
		Array[xs][ys+1].totalCost=Array[xs][ys].totalCost+Array[xs][ys].linkCost[6];
		Array[xs][ys+1].prevNode=&Array[xs][ys];
		if(Array[xs][ys+1].state==0){
		if (xs>1&&xs<size.height-2&&ys>1&&ys<size.width-2){
	//		Node* x=new Node();
	//		*x=Array[xs][ys+1];
			myheap.Insert(&Array[xs][ys+1]);
			Array[xs][ys+1].state=1;
			statecount++;
		}
		
		else if(Array[xs][ys+1].state==1){
			Node* x=new Node();
			*x=Array[xs][ys+1];
			myheap.DecreaseKey(&Array[xs][ys+1],*x);}
	}
	}
	if(Array[xs+1][ys+1].totalCost>Array[xs][ys].totalCost+Array[xs][ys].linkCost[7]){
		Node* y=new Node();
		*y=Array[xs+1][ys+1];
		Array[xs+1][ys+1].totalCost=Array[xs][ys].totalCost+Array[xs][ys].linkCost[7];
		Array[xs+1][ys+1].prevNode=&Array[xs][ys];
		if(Array[xs+1][ys+1].state==0){
		if (xs>1&&xs<size.height-2&&ys>1&&ys<size.width-2){
		//	Node* x=new Node();
		//	*x=Array[xs+1][ys+1];
			myheap.Insert(&Array[xs+1][ys+1]);
			Array[xs+1][ys+1].state=1;
			statecount++;
		}
		}
		else if(Array[xs+1][ys+1].state==1){
			Node* x=new Node();
			*x=Array[xs+1][ys+1];
			myheap.DecreaseKey(&Array[xs+1][ys+1],*x);}
	
	}
	}
}
void drawline(){
	int a,b;
	a=cursorx;
	b=cursory;
	 if(abs(a-seedx)<2&&abs(b-seedy)<2)return;
	 imgb.copyTo(imgf);
	 while(1){
		if(abs(a-seedx)<2&&abs(b-seedy)<2)break;
		if(a<1||b>size.height-2||b<1||a>size.width-2)break;
		line( imgf, Point( a,b ), Point( Array[b][a].prevNode->column, Array[b][a].prevNode->row ) ,Scalar(0,0,0),2);
		line(imgpathtree,Point( 3*a,3*b ), Point( 3*Array[b][a].prevNode->column, 3*Array[b][a].prevNode->row ) ,Scalar(0,0,255),2);
		if(Array[b][a].selected>1){
			mode=2;
			printf("circle");
		}
		b=Array[b][a].prevNode->row;
		a=Array[b][a].prevNode->column;
		
	}
	 imshow("MyWindow",imgf);
	 imshow("PathTree",imgpathtree);
}
void pathtree()
{
	imgpathtree2.copyTo(imgpathtree);
	int a,b;
	for(int i=0;i<size.height;i++){
		for(int j=0;j<size.width;j++){
			 a=j;
			 b=i;
		 while(1){			
		if(abs(a-seedx)<2&&abs(b-seedy)<2)break;
		if(a<1||b>size.height-2||b<1||a>size.width-2)break;
		line( imgpathtree, Point( 3*a,3*b ), Point( 3*Array[b][a].prevNode->column, 3*Array[b][a].prevNode->row ) ,Scalar(1,1,1),1);
		b=Array[b][a].prevNode->row;
		a=Array[b][a].prevNode->column;
		 }
		}
		}
			imshow("PathTree",imgpathtree);
}
void mask(int i,int j){
	Array[i][j].visited=1;
	if(i>0&&i<size.height-1&&j>0&&j<size.width-1){
			for(int z=-1;z<2;z+2){
				if(Array[i][j+z].selected==0&&Array[i][j+z].visited==0){
					imgmask.at<Vec3b>(i,j+z)[0]=0;
					imgmask.at<Vec3b>(i,z+j)[1]=0;
					imgmask.at<Vec3b>(i,j+z)[2]=0;
					mask(i,j+z);
			}
	}
				for(int k=-1;k<2;k+2){
				if(Array[i+k][j].selected==0&&Array[i+k][j].visited==0){
					imgmask.at<Vec3b>(i+k,j)[0]=0;
					imgmask.at<Vec3b>(i+k,j)[1]=0;
					imgmask.at<Vec3b>(i+k,j)[2]=0;
					mask(i+k,j);
			}
	}
}
}
void CallBackFunc(int clickevent, int x, int y, int flags, void* userdata)
{

	cursorx=x;
	cursory=y;
	if(mode==1)drawline();
     if  ( clickevent == EVENT_LBUTTONDOWN )
     {
		 int a,b;
		 a=x;
		 b=y;
		while(mode==1){
		if(abs(a-seedx)<2&&abs(b-seedy)<2)break;
		if(a<1||b>size.height-2||b<1||a>size.width-2)break;
		Array[b][a].selected++;
		b=Array[b][a].prevNode->row;
		a=Array[b][a].prevNode->column;
		
		}
		 statecount=0;
		 for(int i=0;i<size.height;i++){
		 for(int j=0;j<size.width;j++){
			Array[i][j].column=j;
			Array[i][j].row=i;
			Array[i][j].state=0;
			Array[i][j].totalCost=1000000;
			Array[i][j].prevNode=NULL;
		 }
	 }

		 imgf.copyTo(imgb);
		 ShortestPath(x,y);
		 seedx=x;
		 seedy=y;

		 if(mode==0){mode=1;}
		 		 pathtree();
          //cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << mode<<endl;

     }
     else if  ( clickevent == EVENT_RBUTTONDOWN )
     {
		mode=2;
		mask(1,1);
          //cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
     }
     else if  ( clickevent == EVENT_MBUTTONDOWN )
     {
          //cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
     }
     else if ( clickevent == EVENT_MOUSEMOVE )
     {
          //cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;

     }
}

void callbackButton(int state, void* pointer)
{
	printf("button");
}
int main( int argc, const char** argv )
{
	string filename; 
	double maxd=0.0;
//	getline(cin,filename);
	filename="ferry.bmp";
	myheap=FibHeap();
	imginit=imread("ferry.bmp", CV_LOAD_IMAGE_UNCHANGED);
     imgf = imread(filename, CV_LOAD_IMAGE_UNCHANGED); //read the image data in the file "MyPic.JPG" and store it in 'img'
	 imgb = imread(filename, CV_LOAD_IMAGE_UNCHANGED);
	 img = imread(filename, CV_LOAD_IMAGE_UNCHANGED);
	 size= imgf.size();
	 imgpn=Mat::Mat(size.height*3,size.width*3,imgf.type(),Scalar(255,255,255));
	 costgraph=Mat::Mat((size.height-2)*3,(size.width-2)*3,CV_8UC1);
	 imgpathtree=Mat::Mat(size.height*3,size.width*3,imgf.type(),Scalar(255,255,255));
	 imgpathtree2=Mat::Mat(size.height*3,size.width*3,imgf.type(),Scalar(255,255,255));
	 imgmask=Mat::Mat(size.height,size.width,imgf.type(),Scalar(255,255,255));
     if (imgf.empty()) //check whether the image is loaded or not
     {
          cout << "Error : Image cannot be loaded..!!" << endl;
          //system("pause"); //wait for a key press
          return -1;
     }


	 printf("%i %i\n",size.height,size.width);
	 Array =new Node *[size.height];
	 for(int i=0;i<size.height;i++)
		 Array[i]=new Node[size.width];
	 for(int i=1;i<size.height-1;i++){
		 for(int j=1;j<size.width-1;j++){

			Point3_<uchar>* p0 = imgf.ptr<Point3_<uchar> >(i+1,j);
			Point3_<uchar>* p1 = imgf.ptr<Point3_<uchar> >(i+1,j-1);
			Point3_<uchar>* p2 = imgf.ptr<Point3_<uchar> >(i,j-1);
			Point3_<uchar>* p3 = imgf.ptr<Point3_<uchar> >(i-1,j-1);
			Point3_<uchar>* p4 = imgf.ptr<Point3_<uchar> >(i-1,j);
			Point3_<uchar>* p5 = imgf.ptr<Point3_<uchar> >(i-1,j+1);
			Point3_<uchar>* p6 = imgf.ptr<Point3_<uchar> >(i,j+1);
			Point3_<uchar>* p7 = imgf.ptr<Point3_<uchar> >(i+1,j+1);
			Array[i][j].linkCost[0]=sqrt((pow(double (abs(abs(p1->x-p2->x)/2-abs(p7->x-p6->x)/2)/2), 2)+pow(double (abs(abs(p1->y-p2->y)/2-abs(p7->y-p6->y)/2)/2), 2)+pow(double (abs(abs(p1->y-p2->y)/2-abs(p7->y-p6->y)/2)/2), 2))/3);
			Array[i][j].linkCost[1]=sqrt((pow(abs(p0->x-p2->x)/sqrt(2.0),2)+pow(abs(p0->y-p2->y)/sqrt(2.0),2)+pow(abs(p0->z-p2->z)/sqrt(2.0),2))/3);
			Array[i][j].linkCost[2]=sqrt((pow(double (abs(abs(p1->x-p0->x)/2-abs(p3->x-p4->x)/2)/2), 2)+pow(double (abs(abs(p1->y-p0->y)/2-abs(p4->y-p3->y)/2)/2), 2)+pow(double (abs(abs(p1->y-p0->y)/2-abs(p4->y-p3->y)/2)/2), 2))/3);
			Array[i][j].linkCost[3]=sqrt((pow(abs(p4->x-p2->x)/sqrt(2.0),2)+pow(abs(p4->y-p2->y)/sqrt(2.0),2)+pow(abs(p4->z-p2->z)/sqrt(2.0),2))/3);
			Array[i][j].linkCost[4]=sqrt((pow(double (abs(abs(p3->x-p2->x)/2-abs(p5->x-p6->x)/2)/2), 2)+pow(double (abs(abs(p3->y-p2->y)/2-abs(p5->y-p6->y)/2)/2), 2)+pow(double (abs(abs(p3->y-p2->y)/2-abs(p5->y-p6->y)/2)/2), 2))/3);
			Array[i][j].linkCost[5]=sqrt((pow(abs(p4->x-p6->x)/sqrt(2.0),2)+pow(abs(p4->y-p6->y)/sqrt(2.0),2)+pow(abs(p4->z-p6->z)/sqrt(2.0),2))/3);
			Array[i][j].linkCost[6]=sqrt((pow(double (abs(abs(p4->x-p5->x)/2-abs(p7->x-p0->x)/2)/2), 2)+pow(double (abs(abs(p4->y-p5->y)/2-abs(p7->y-p0->y)/2)/2), 2)+pow(double (abs(abs(p4->y-p5->y)/2-abs(p7->y-p0->y)/2)/2), 2))/3);
			Array[i][j].linkCost[7]=sqrt((pow(abs(p0->x-p6->x)/sqrt(2.0),2)+pow(abs(p0->y-p6->y)/sqrt(2.0),2)+pow(abs(p0->z-p6->z)/sqrt(2.0),2))/3);

			for(int k=0;k<8;k++){
				if(Array[i][j].linkCost[k]>maxd)
					maxd=Array[i][j].linkCost[k];
			}


		 }
	 }
	 for(int i=0;i<size.height;i++){
		 for(int j=0;j<size.width;j++){
			Array[i][j].column=j;
			Array[i][j].row=i;
			Array[i][j].state=0;
			Array[i][j].totalCost=1000000;
			Array[i][j].prevNode=NULL;
		 }
	 }
	 for(int i=1;i<size.height-1;i++){
		 for(int j=1;j<size.width-1;j++){
			Array[i][j].linkCost[0]=maxd-Array[i][j].linkCost[0];
			Array[i][j].linkCost[1]=(maxd-Array[i][j].linkCost[1])*sqrt(2.0);
			Array[i][j].linkCost[2]=maxd-Array[i][j].linkCost[2];
			Array[i][j].linkCost[3]=(maxd-Array[i][j].linkCost[3])*sqrt(2.0);
			Array[i][j].linkCost[6]=maxd-Array[i][j].linkCost[6];
			Array[i][j].linkCost[5]=(maxd-Array[i][j].linkCost[5])*sqrt(2.0);
			Array[i][j].linkCost[4]=maxd-Array[i][j].linkCost[4];
			Array[i][j].linkCost[7]=(maxd-Array[i][j].linkCost[7])*sqrt(2.0);
		
		 }
	 }
	 for(int i=0;i<size.height;i++){
		 for(int j=0;j<size.width;j++){
			 imgpn.at<Vec3b>(3*i,3*j)[0]=imgf.at<Vec3b>(i,j)[0];
			imgpn.at<Vec3b>(3*i,3*j)[1]=imgf.at<Vec3b>(i,j)[1];
			imgpn.at<Vec3b>(3*i,3*j)[2]=imgf.at<Vec3b>(i,j)[2];
		 }
	 }
//	 line( img, Point( 0, 15*size.width/16 ), Point( size.height, 15*size.width/16 ) ,Scalar(0,0,0));
	 // hugiyugyui
	 int value=50;
     namedWindow("MyWindow", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"
	 namedWindow("CostGraph", CV_WINDOW_AUTOSIZE);
	 namedWindow("PathTree",CV_WINDOW_AUTOSIZE);
	 namedWindow("pixelNode",CV_WINDOW_AUTOSIZE);
	 namedWindow("Mask",CV_WINDOW_AUTOSIZE);

	 for(int i=1;i<size.height-1;i++){
		 for(int j=1;j<size.width-1;j++){
		 costgraph.at<uchar>(i*3-2,j*3-2)=0;
		 costgraph.at<uchar>(i*3-1,j*3-2)=(uchar) Array[i][j].linkCost[0];
		 costgraph.at<uchar>(i*3-1,j*3-3)=(uchar) Array[i][j].linkCost[1];
		 costgraph.at<uchar>(i*3-2,j*3-3)=(uchar) Array[i][j].linkCost[2];
		 costgraph.at<uchar>(i*3-3,j*3-3)=(uchar) Array[i][j].linkCost[3];
		 costgraph.at<uchar>(i*3-3,j*3-2)=(uchar) Array[i][j].linkCost[4];
		 costgraph.at<uchar>(i*3-3,j*3-1)=(uchar) Array[i][j].linkCost[5];
		 costgraph.at<uchar>(i*3-2,j*3-1)=(uchar) Array[i][j].linkCost[6];
		 costgraph.at<uchar>(i*3-1,j*3-1)=(uchar) Array[i][j].linkCost[7];
		 }
	 }
//	 createButton("button1",callbackButton);
  //   createButton("button2",callbackButton);
	 setMouseCallback("MyWindow", CallBackFunc, NULL);
     imshow("MyWindow", imgf); //display the image which is stored in the 'img' in the "MyWindow" window
	 imshow("PathTree",imgpathtree);
	 imshow("CostGraph",costgraph);
	 imshow("pixelNode",imgpn);
	 imshow("Mask",imgmask);
     waitKey(0); //wait infinite time for a keypress

     destroyWindow("MyWindow"); //destroy the window with the name, "MyWindow"
	  destroyWindow("CostGraph");
	   destroyWindow("PathTree");
	   destroyWindow("pixelNode");
     return 0;
}


