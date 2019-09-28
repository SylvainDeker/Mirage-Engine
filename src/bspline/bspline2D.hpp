#ifndef BSPLINE2D_H_
#define BSPLINE2D_H_
#include <vector>

#include "../glm/glm.hpp"


/*!
   \file bSpline2D
   \brief Class aimed at calculate vertices of the surface from control points
   \author "Your name"
   \date "DD"/"Month"/"Year"
*/
class BSpline2D{
public:

  /*!
     \brief Constructor
     \param A reference to the control Points vector (the dimensions x,y are init later ) (this vector can be fill later)
  */
  BSpline2D(
         std::vector<glm::vec3>& controlPoints);

  /*!
     \brief Set the order K of the BSpline function of the dimension X
     \param K
  */
  void setOrderKX(int k);


  /*!
  \brief Set the order K of the BSpline function of the dimension Y
  \param K
  */
  void setOrderKY(int k);

  /*!
  \brief Get the order K of the BSpline function of the dimension X
  \return K
  */
  int getOrderKX() const ;

  /*!
  \brief Get the order K of the BSpline function of the dimension Y
  \return K
  */
  int getOrderKY() const ;

  /*!
  \brief Get the N of the BSpline function of the dimension X (N+1 is number of control points )
  \return N
  */
  int getNX() const ;

  /*!
  \brief Get the N of the BSpline function of the dimension Y (N+1 is number of control points )
  \return N
  */
  int getNY() const ;

  /*!
     \brief Set N number where N+1 is the number of control point on the dimension X
     \param N
  */
  void setNX(int n);

  /*!
  \brief Set N number where N+1 is the number of control point on the dimension Y
  \param N
  */
  void setNY(int n);

  /*!
     \brief Initialize Modal vectors on X and Y
     \param modalVectorX
     \param modalVectorY
     \pre Order k and N must be already initialized by using setOrderKX(), setOrderKY, setNX(), setNY() and control pointsmust be added to controlPoints vector (which was given to the Constructor)
  */
  void setModalVectors(const std::vector<float> & modalVectorX, const std::vector<float> & modalVectorY);

  /*!
     \brief Initialize Modal vectors on X and Y with a default uniform modal vector (on X and Y)
     \pre Order k and N must be already initialized by using setOrderKX(), setOrderKY, setNX(), setNY() and control pointsmust be added to controlPoints vector (which was given to the Constructor)
  */
  void setModalVectors();

  /*!
     \brief Get a discret vector of vertices to render
     \param Number reference to the vector to fill (add in queue)
     \param Number of discret points on X
     \param Number of discret points on Y
     \pre ModalVectors must be initialized see setModalVectors()
  */
  void getDisplayPoints(std::vector<glm::vec3> & vertices,size_t pointsX,size_t pointsY) const ;




private:

  /*!
     \brief polynom give the 3D discret coord in from the 2D coord along the surface.
     \param u is along X
     \param v is along Y
     \pre setModalVectors() must be initialized
     \return the 3D coord (global word)
  */
  glm::vec3 polynom(float u,float v) const ;

  /*!
     \brief Get the index of a vector from two coord x and y;
     \param x
     \param y
     \return the index
  */
  size_t getIdx(size_t x,size_t y) const ;

  /*!
     \brief Calculate the floraison with the recursive algorithm over 1 dimension
     \param u is used to iterate the dimension
     \param k is the order k
     \param i is i+1th control point on the current dimension
     \param modalVector of the current dimension
     \pre setModalVectors() must be initialized
     \return a weigth that means how much this contribution worth in i
  */
  float recFloraison(float u,int k,int i,const std::vector<float> & modalVector) const ;

  // _controlPoints doesn't belong to this class (avoid useless copy in the memory)
  std::vector<glm::vec3> &_controlPoints;
  // modalVector, orders ans the n are only used to calcul bspline so it's own to this class
  std::vector<float> _modalVectorX;
  std::vector<float> _modalVectorY;
  int _order_kx;
  int _order_ky;
  int _nx;
  int _ny;


};


















#endif // BSPLINE2D_H_
