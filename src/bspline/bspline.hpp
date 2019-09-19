#ifndef BSPLINE_H_
#define BSPLINE_H_
#include <vector>

#include "../glm/glm.hpp"


/*!
   \file bSpline
   \brief Class aimed at calculate vertices of the surface from control points
*/
class BSpline{
public:

  /*!
     \brief Constructor
     \param A reference to the control Points vector (this vector can be fill later)
  */
  BSpline(std::vector<glm::vec3>& controlPoints);

  /*!
     \brief Set the order K of the BSpline function
     \param K
  */
  void setOrderK(int k);

  /*!
  \brief Get the order K of the BSpline function
  \return K
  */
  int getOrderK() const ;

  /*!
  \brief Get the N of the BSpline function (N+1 is number of control points )
  \return N
  */
  int getN() const ;

  /*!
     \brief Initialize Modal vectors with a default uniform modal vector
     \pre Order k and N must be already initialized by using setOrderK() and control pointsmust be added to controlPoints vector (which was given to the Constructor)
  */
  void setModalVector();

  /*!
     \brief Initialize Modal vectors
     \param modalVector
     \pre Order k and N must be already initialized by using setOrderK()and control pointsmust be added to controlPoints vector (which was given to the Constructor)
  */
  void setModalVectors(const std::vector<float> & modalVectorX);

  /*!
     \brief Get a discret vector of vertices to render
     \param Number reference to the vector to fill (add in queue)
     \param Number of discret points
     \pre ModalVector must be initialized see setModalVectors()
  */
  void getDisplayPoints(std::vector<glm::vec3> & vertices,size_t points) const ;

private:
  /*!
     \brief polynom give the 3D discret coord in from the 2D coord along the surface.
     \param u
     \pre setModalVector() must be initialized
     \return the 3D coord (global world)
  */
  glm::vec3 polynom(float u) const ;


  glm::vec3 floraison(float u) const ;
  float recFloraison(float u,int k,int i) const ;

  std::vector<glm::vec3> &_controlPoints;
  std::vector<float> _modalVector;
  int _order_k;


};


















#endif // BSPLINE_H_
