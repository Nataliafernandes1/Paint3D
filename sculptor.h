#ifndef SCULPTOR_H
#define SCULPTOR_H

struct Voxel {
  float r,g,b; // Colors
  float a;
// Transparency
  bool isOn; // Included or not
};
/**
* @brief A classe Sculptor serve para manipular os pixels de uma matriz tridimensional
        */
class Sculptor {
protected:
  Voxel ***v;
  int nx,ny,nz; // Dimensions
  float r,g,b,a; // Current drawing color
public:
  /**
   * @brief Sculptor Construtor da classe
   * @param _nx valor inicial de nx
   * @param _ny valor inicial de ny
   * @param _nz valor inicial de nz
   */
  Sculptor(int _nx, int _ny, int _nz);
   /**
  * @brief ~Sculptor eh o destrutor da classe
  */
  ~Sculptor();
  /**
   * @brief setColor Define a cor atual do desenho
   * @param r_ Define a cor vermelha
   * @param g_ Define a cor verde
   * @param b_ Define a cor azul
   * @param alpha_ Define se eh opaco
   */
  void setColor(float r_, float g_, float b_, float alpha_);
  /**
    * @brief putVoxel Ativa o voxel na posição (x,y,z) (fazendo isOn = true) e atribui ao mesmo a cor     atual de desenho
    * @param x posição "x"
    * @param y posição "y"
    * @param z posição "z"
    */
  void putVoxel(int x, int y, int z);
  /**
    * @brief cutVoxel Desativa o voxel na posição (x,y,z) (fazendo isOn = false)
    * @param x posição "x"
    * @param y posição "y"
    * @param z posição "z"
    */
  void cutVoxel(int x, int y, int z);
  /**
    * @brief putBoxel Ativa todos os voxels no intervalo x∈[x0,x1], y∈[y0,y1], z∈[z0,z1] e atribui aos mesmos a cor atual de desenho
    * @param x0 posição "x0" incial.
    * @param x1 posição "x1" final.
    * @param y0 posição "y0" incial.
    * @param y1 posição "y1" final.
    * @param z0 posição "z0" incial.
    * @param z1 posição "z1" final.
    */
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
  /**
    * @brief cutBox Desativa todos os voxels no intervalo x∈[x0,x1], y∈[y0,y1], z∈[z0,z1] e atribui aos mesmos a cor atual de desenho
    * @param x0 posição "x0" incial.
    * @param x1 posição "x1" final.
    * @param y0 posição "y0" incial.
    * @param y1 posição "y1" final.
    * @param z0 posição "z0" incial.
    * @param z1 posição "z1" final.
    */
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
  /**
    * @brief putSphere Ativa todos os voxels que satisfazem à equação da esfera e atribui aos mesmos a cor atual de desenho (r,g,b,a)
    * @param xcenter centro da esfera na cordenada x.
    * @param ycenter centro da esfera na cordenada y.
    * @param zcenter centro da esfera na cordenada z.
    * @param radius raio da esfera
    */
  void putSphere(int xcenter, int ycenter, int zcenter, int radius);
  /**
    * @brief cutSphere Desativa todos os voxels que satisfazem à equação da esfera
    * @param xcenter centro da esfera na cordenada x.
    * @param ycenter centro da esfera na cordenada y.
    * @param zcenter centro da esfera na cordenada z.
    * @param radius raio da esfera
    */
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
  /**
    * @brief putEllipsoid Ativa todos os voxels que satisfazem à equação do elipsóide e atribui aos mesmos a cor atual de desenho
    * @param xcenter centro da elipsóide na cordenada x.
    * @param ycenter centro da elipsóide na cordenada y.
    * @param zcenter centro da elipsóide na cordenada z.
    * @param rx semi-eixo principal x da elipsóide
    * @param ry semi-eixo principal y da elipsóide
    * @param rz semi-eixo principal z da elipsóide
    */
  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  /**
    * @brief cutEllipsoid Desativa todos os voxels que satisfazem à equação do elipsóide
    * @param xcenter centro da elipsóide na cordenada x.
    * @param ycenter centro da elipsóide na cordenada y.
    * @param zcenter centro da elipsóide na cordenada z.
    * @param rx semi-eixo principal x da elipsóide
    * @param ry semi-eixo principal y da elipsóide
    * @param rz semi-eixo principal z da elipsóide
    */
  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  /**
    * @brief writeOFF grava a escultura no formato OFF no arquivo filename
    */
  void writeOFF(char *filename);
};

#endif // SCULPTOR_H
