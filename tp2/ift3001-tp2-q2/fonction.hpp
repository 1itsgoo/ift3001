#ifndef FONCTION
#define FONCTION

// Classe abstraite representant une fonction prenant en entree un entier et retournant un entier
class Fonction {
public:
  virtual ~Fonction() {};
  virtual int evaluer(int x) const = 0;
};

// Fonction lineaire f(x) = m * x + b
class FonctionLineaire : public Fonction {
private:
  const int m_m;
  const int m_b;
public:
  FonctionLineaire(int m, int b)
    : m_m(m),
      m_b(b)
  {}

  virtual int evaluer(int x) const {
    return m_m * x + m_b;
  }
};

// Fonction f(x) = max(pente * (x - seuil), 0)
class FonctionBatonHockey : public Fonction {
private:
  const int m_seuil;
  const int m_pente;
public:
  FonctionBatonHockey(int seuil, int pente)
    : m_seuil(seuil),
      m_pente(pente)
  {}

  virtual int evaluer(int x) const {
    if (x <= m_seuil)
      return 0;
    return (x - m_seuil) * m_pente;
  }
};

// Fonction f(x) = x^2
class FonctionCarre : public Fonction {
public:
  FonctionCarre() {}
  virtual int evaluer(int x) const {
    return x * x;
  }
};

#endif
