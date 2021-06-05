#include <cmath>
#include <math.h>
#include <cstdlib>
#include <time.h>

const int NUMBER_OF_PARTICLES = 3000;
const float MAX_ROTATION = 360;
const float MIN_ROTATION = 0;
const float MIN_TRANS = .005;
const float MAX_TRANS = .03;
const float MIN_DELTA_ROTATION = 0.5;
const float MAX_DELTA_ROTATION = 3.0;
const float MIN_DELTA_SURFACE = .005;
const float MAX_DELTA_SURFACE = .01;
const int MIN_LIFETIME = 10;
const int MAX_LIFETIME = 25;
const int DELTA_LIFETIME = 1;


struct Particle{
		//������ӵĳ�ʼλ��
		float azimuthRoation, zenithRotation, surfaceTranslationFactor;

		//������ӵı仯
		float deltaAz, deltaZe, deltaSurface;

		//���ʱ��
		int lifetime;
};
		//����ϵͳ
class ParticleSystem{
	
	public: 
		
		Particle getNextParticle();
		//�޸��������ӣ�ɾ���ϵģ������µ�����
		void updateAll();
		int getNumberOfParticles();
		ParticleSystem();


	private:
		//׷������λ��
		int currentParticle;

		//��¼����������Ϣ
		Particle particles[NUMBER_OF_PARTICLES];

	  
		float generateRandomNumber(float lower, float upper);
		
		//�������һ������
		Particle generateNewParticle();

};

ParticleSystem::ParticleSystem(){
	currentParticle = 0;
	for(int i = 0; i < NUMBER_OF_PARTICLES; i++){
		particles[i] = generateNewParticle();
	}
}

Particle ParticleSystem::generateNewParticle(){
	Particle newPart;
		newPart.azimuthRoation = generateRandomNumber(MIN_ROTATION, MAX_ROTATION);
		newPart.zenithRotation = generateRandomNumber(MIN_ROTATION, MAX_ROTATION);
		newPart.surfaceTranslationFactor = generateRandomNumber(MIN_TRANS, MAX_TRANS);
		newPart.deltaAz = generateRandomNumber(MIN_DELTA_ROTATION, MAX_DELTA_ROTATION);
		newPart.deltaZe = generateRandomNumber(MIN_DELTA_ROTATION, MAX_DELTA_ROTATION);
		newPart.deltaSurface = generateRandomNumber(MIN_DELTA_SURFACE, MAX_DELTA_SURFACE);
		newPart.lifetime = (int)generateRandomNumber(MIN_LIFETIME, MAX_LIFETIME);
		return newPart;
}

Particle ParticleSystem::getNextParticle(){
	currentParticle = (currentParticle == NUMBER_OF_PARTICLES) ? 0 : currentParticle;
	return particles[currentParticle++];
}

int ParticleSystem::getNumberOfParticles(){
	return NUMBER_OF_PARTICLES;
}

float ParticleSystem::generateRandomNumber(float lower, float upper){
	static bool firstTime = true;
	time_t randomNumberSeed;

	if (firstTime){
		time(&randomNumberSeed);
		srand(randomNumberSeed);
		firstTime = false;
	}
	return (lower + ((upper - lower) * (float(rand()) / RAND_MAX)));
}

void ParticleSystem::updateAll(){
	//���һ�����ӵĴ��ʱ���ѵ�ɾ���ɵģ����µ��滻
	//����������²�������
	for(int i = 0; i < NUMBER_OF_PARTICLES; i++){
		if(particles[i].lifetime == 0){
			particles[i] = generateNewParticle();
		}else{
			particles[i].azimuthRoation += particles[i].deltaAz;
			particles[i].zenithRotation += particles[i].deltaZe;
			particles[i].surfaceTranslationFactor += particles[i].deltaSurface;
			particles[i].lifetime -= DELTA_LIFETIME;
		}
	}
}


