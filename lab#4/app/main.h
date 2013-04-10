#define NUMLIFEFORMS ((int) (sizeof lifeforms / sizeof lifeforms[0]))

struct {
  int pixel;
  int squares;
  bool* pMap;
  LPSTR szLabel;
}
lifeforms[] = {
  0, 0, NULL, "Blinker",
  0, 0, NULL, "Glider",
  0, 0, NULL, "Spaceship",
  0, 0, NULL, "Pulsar",
  0, 0, NULL, "Gosper Glider Gun",
  0, 0, NULL, "Draw Some!"
};