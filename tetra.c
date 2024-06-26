                                                #include<stdio.h>
                                              #include<math.h>
                                            #include<stdlib.h>
                                          #include<string.h>
                                        #include<unistd.h>
                                      #define W 160
                                    #define H 44
                                  #define P 100
                                #define T 12
                            float A,B,C,w=20,Z[W*H]; char b[W*H],F[]={'#','*','=','.'};
                            float V[4][3]={{-1,-1,-1},{1,-1,1},{-1,1,1},{1,1,-1}};
                            int f[4][3]={{0,1,2},{0,1,3},{0,2,3},{1,2,3}};
                          float X(float i,float j,float k){return j*sin(A)*sin(B)*cos(C)
                      -k*cos(A)*sin(B)*cos(C)+j*cos(A)*sin(C)+k*sin(A)*sin(C)+i*cos(B)*cos(C);}
                  float Y(float i,float j,float k){return j*cos(A)*cos(C)+k*sin(A)*cos(C)-j*sin(A)*sin(B)
              *sin(C)+k*cos(A)*sin(B)*sin(C)-i*cos(B)*sin(C);}float S(float i,float j,float k){return k*cos(A)*cos(B)-j*sin(A)*cos(B)
          +i*sin(B);}void R(float x,float y,float z,char c){float a=X(x,y,z),e=Y(x,y,z),d=S(x,y,z)+P,o=1/d;int p=(W/2+T*2*o*a),q=(H/2+T*o*e);
      if(p>=0&&p<W&&q>=0&&q<H){int i=p+q*W;if(o>Z[i]){Z[i]=o;b[i]=c;}}}void U(float A,float B,float C){memset(b,' ',W*H);memset(Z,0,W*H*sizeof(float));
  for(int g=0;g<4;g++){float v1x=V[f[g][0]][0]*w,v1y=V[f[g][0]][1]*w,v1z=V[f[g][0]][2]*w,v2x=V[f[g][1]][0]*w,v2y=V[f[g][1]][1]*w,v2z=V[f[g][1]][2]*w,
v3x=V[f[g][2]][0]*w,v3y=V[f[g][2]][1]*w,v3z=V[f[g][2]][2]*w;for(float i=0;i<1;i+=.01)for(float j=0;j<1-i;j+=.01){float x=v1x+(v2x-v1x)*i+(v3x-v1x)*j,
y=v1y+(v2y-v1y)*i+(v3y-v1y)*j,z=v1z+(v2z-v1z)*i+(v3z-v1z)*j;R(x,y,z,F[g]);}}printf("\x1b[H");for(int k=0;k<W*H;k++)putchar(k%W?b[k]:10);}int main(){
printf("\x1b[2J");while(1){U(A,B,C);A+=.05;B+=.05;C+=.01;usleep(30000);}return 0;}
