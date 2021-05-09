class Motor {
  public: 
    Motor(int pinA, int pinB, int pinC, int pinD);
    void setFrequency(float freq);
    void init();
    void tick();
    void enable();
    void disable();
    bool state;
    void nextStep();
    void resetPort();
    void lock();
  private:
    int A;
    int B;
    int C;
    int D;

    int step;
    unsigned long usSinceLastStep;
    long usPeriod;
};