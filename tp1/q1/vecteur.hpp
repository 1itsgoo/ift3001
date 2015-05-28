#ifndef VECTEUR
#define VECTEUR

class Vecteur {
private:
  int capacite_;
  int taille_;
  int* entiers_;
public:
  Vecteur(int capacite);
  Vecteur(int capacite, int* elements_initiaux);
  virtual ~Vecteur();

  int operator[](int index) const;
  bool operator==(const Vecteur& autre_vecteur) const;
  int taille() const;

  void ajouteEntier(int entier);
  void supprimeEntier(int position);
  void supprimeEntiers(const Vecteur& index);
};

#endif
