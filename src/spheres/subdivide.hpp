#ifndef SUBDIVIDE_H
#define SUBDIVIDE_H


class SubDivide{
public:
  SubDivide(std::vector<GLfloat> & vertices,
    std::vector<GLfloat> & normals,
    std::vector<GLuint> & indices);
  void setCoef(const GLfloat coef);
  void run();
private:
  struct Edge{
    GLuint pt1,pt2;
    GLuint center;
  };

  std::vector<GLfloat> &_vertices;
  std::vector<GLfloat> &_normals;
  std::vector<GLuint> &_indices;
  GLfloat _coef;
  std::vector<GLuint> _newindices;
  std::vector<Edge> _indexEdge;
  inline glm::vec3 getNorm(const GLuint index_vertex) const ;
  inline glm::vec3 getCoord(const GLuint index_vertex) const ;
  inline void getIndexTriangle(const GLuint index_trinagle,GLuint &index_vertex1,GLuint &index_vertex2,GLuint &index_vertex3) const ;
  inline void addTriangle(GLuint const index_vertex1,GLuint const index_vertex2,GLuint const index_vertex3);
  inline GLuint addVertex(const glm::vec3 coord,const glm::vec3 norm);
  bool findEdge(const GLuint index_vertex_a,const GLuint index_vertex_b, GLuint & res);
  void build_sub_triangle(const GLuint index_vertex_a,
                                        const GLuint index_vertex_b,
                                        const GLuint index_vertex_c,
                                        GLuint & index_vertex_d,
                                        GLuint & index_vertex_e,
                                        GLuint & index_vertex_f);
  GLuint associateVertex(const GLuint index_vertex_a, const GLuint index_vertex_b,const GLfloat coef);
};


#endif // SUBDIVIDE_H
