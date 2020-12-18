#include "sculptor.h"
#include<iostream>
#include<fstream>
#include<cstdlib>


Sculptor::Sculptor(int _nx, int _ny, int _nz)
{
    nx=_nx;
    ny=_ny;
    nz=_nz;
    v=new Voxel**[nx];
    v[0]=new Voxel*[nx*ny];
    v[0][0]=new Voxel[nx*ny*nz];
    for (int i=0; i<nx; i++)
    {
        v[i]=v[i-1]+ny;
    }
    for(int i=1; i<nx*ny; i++)
    {
        v[0][i]=v[0][i-1]+nz;
    }
    for (int i=0; i<nx; i++)
    {
        for(int j=0; j<ny; j++)
        {
            for(int k=0; k<nz; k++)
        {
            v[i][j][k].isOn=false;
    }
    }
    }
}

Sculptor::~Sculptor()
{
    if(nx<0 || ny < 0 || nz < 0)
       {
           return;
       }
       delete [] v[0][0];
       delete [] v[0];
       delete [] v;
}

void Sculptor::setColor(float r_, float g_, float b_, float alpha_)
{
    r=r_; g=g_; b=b_; a=alpha_;

}

void Sculptor::putVoxel(int x, int y, int z)
{
    if (x>0 && x<nx && y>=0 && y<ny && z>=0 && z<nz)
    {
        v[x][y][z].isOn = true;
        v[x][y][z].r = r;
        v[x][y][z].g = g;
        v[x][y][z].b = b;
        v[x][y][z].a = a;
    }
}

void Sculptor::cutVoxel(int x, int y, int z)
{
    if(x>=0 && x<nx && y>=0 && y<ny && z>=0 && z<nz)
    {
        v[x][y][z].isOn = false;
    }
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
        for(int i = 0; i<nx; i++){
            for(int j = 0; j<ny; j++){
                for(int k = 0; k<nz; k++){
                    if(i>=x0 && i<=x1 && j>=y0 && j<=y1 && k>=z0 && k<=z1){
                        v[i][j][k].isOn = true;
                        v[i][j][k].r = r;
                        v[i][j][k].g = g;
                        v[i][j][k].b = b;
                        v[i][j][k].a = a;
                    }
                }
            }
        }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
        for(int i = 0; i<nx; i++){
            for(int j = 0; j<ny; j++){
                for(int k = 0; k<nz; k++){
                    if(i>=x0 && i<=x1 && j>=y0 && j<=y1 && k>=z0 && k<=z1){
                        v[i][j][k].isOn = false;
                    }
                }
            }
        }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius)
{
        for(int i = 0; i<nx; i++){
            for(int j = 0; j<ny; j++){
                for(int k = 0; k<nz; k++){
                    if(((i - xcenter)*(i-xcenter)+(j-ycenter)*(j-ycenter)+(k-zcenter)*(k-zcenter))<=radius*radius)
                    {
                        v[i][j][k].isOn = true;
                        v[i][j][k].r = r;
                        v[i][j][k].g = g;
                        v[i][j][k].b = b;
                        v[i][j][k].a = a;
                    }
                }
            }
        }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius)
{
        for(int i = 0; i<nx; i++){
            for(int j = 0; j<ny; j++){
                for(int k = 0; k<nz; k++){
                    if(((i-xcenter)*(i-xcenter)+(j-ycenter)*(j-ycenter)+(k-zcenter)*(k-zcenter))<=radius*radius)
                    {
                        v[i][j][k].isOn = false;
                    }
                }
            }
        }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
        for(int i = 0; i<nx; i++){
            for(int j = 0; j<ny; j++){
                for(int k = 0; k<nz; k++){
                    if((((i-xcenter)*(i-xcenter))/(float)(rx*rx)+((j-ycenter)*(j-ycenter))/(float)(ry*ry)+((k-zcenter)*(k-zcenter))/(float)(rz*rz))<=1)
                    {
                        v[i][j][k].isOn = true;
                        v[i][j][k].r = r;
                        v[i][j][k].g = g;
                        v[i][j][k].b = b;
                        v[i][j][k].a = a;
                    }
                }
            }
        }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
        for(int i = 0; i<nx; i++){
            for(int j = 0; j<ny; j++){
                for(int k = 0; k<nz; k++){
                    if((((i-xcenter)*(i-xcenter))/(float)(rx*rx)+((j-ycenter)*(j-ycenter))/(float)(ry*ry)+ ((k-zcenter)*(k-zcenter))/(float)(rz*rz))<=1)
                    {
                        v[i][j][k].isOn = false;
                    }
                }
            }
        }
}



void Sculptor::writeOFF(char *filename)
{
    //numero de voxel
    int n_voxel = 0;

    //matriz auxiliar para verificacao do voxel e seu arredor
    int aux[nx][ny][nz];
    bool test_x, test_y, test_z;


    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                aux[i][j][k] = 0;
            }}}


   std:: ofstream outfile (filename);
    outfile<<"OFF"<<std::endl;
    for(int i = 0; i < nx-2; i++){
        for(int j = 0; j < ny-2; j++){
            for(int k = 0; k < nz-2; k++){
                test_x = false, test_y = false, test_z=false;

                //Verificacao ao redor do voxel
                if(v[i][j][k].isOn && v[i+2][j][k].isOn){
                    test_x = true;
                }
                if(v[i][j][k].isOn && v[i][j+2][k].isOn){
                    test_y = true;
                }
                if(v[i][j][k].isOn && v[i][j][k+2].isOn){
                    test_z = true;
                }
                if(test_x || test_y || test_z){
                    aux[i+1][j+1][k+1] = 1;
                }}}}

    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                if (v[i][j][k].isOn && aux[i][j][k] == 0){
                    n_voxel++;
                }}}}


    outfile << 8*n_voxel << " " << 6*n_voxel << " " << 0 << std::endl;
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                if (v[i][j][k].isOn && aux[i][j][k] == 0){
                    outfile << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
                    outfile << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
                    outfile << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
                    outfile << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
                    outfile << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
                    outfile << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
                    outfile << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
                    outfile << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
                }}}}
    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            for(int k = 0; k < nz; k++)
            {
                if (v[i][j][k].isOn && aux[i][j][k] ==0)
                {
                    outfile << 4 << " " << 0 + 8*i << " " << 3 + 8*i << " " << 2 + 8*i << " " << 1 + 8*i << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << " " << std::endl;
                    outfile << 4 << " " << 4 + 8*i << " " << 5 + 8*i << " " << 6 + 8*i << " " << 7 + 8*i << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << " " << std::endl;
                    outfile << 4 << " " << 0 + 8*i << " " << 1 + 8*i << " " << 5 + 8*i << " " << 4 + 8*i << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << " " << std::endl;
                    outfile << 4 << " " << 0 + 8*i << " " << 4 + 8*i << " " << 7 + 8*i << " " << 3 + 8*i << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << " " << std::endl;
                    outfile << 4 << " " << 3 + 8*i << " " << 7 + 8*i << " " << 6 + 8*i << " " << 2 + 8*i << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << " " << std::endl;
                    outfile << 4 << " " << 1 + 8*i << " " << 2 + 8*i << " " << 6 + 8*i << " " << 5 + 8*i << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << " " << std::endl;
                }}}}

    outfile.close();
}
