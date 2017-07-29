#include <cstdio>
#include <cmath>
#include <vector>
#include <SFML/Audio.hpp>

int16_t signalSquelch = 100;

int16_t Squelch(int16_t s){
	if(abs(s) < signalSquelch){
		return 0;
	}
	return s;
}

int8_t Regenerate(int16_t s){
	int16_t sq = Squelch(s);
	if(sq == 0){
		return 0;
	}else if(sq > 0){
		return 127;
	}
	return -127;
}

int main(int argc, char **argv)
{
	
	sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("e7c48e6e7a0e12dc4a15dac76c5936dfb8314d48_recording.wav")){
		return -1;
	}
	
	const int16_t *samples = buffer.getSamples();
	const size_t samplesCount = buffer.getSampleCount();
	const unsigned int sampleRate = buffer.getSampleRate();
	std::vector<size_t> freqData;
	
	printf("Samples count:\t%zd\nSample Rate:\t%d\n", samplesCount, sampleRate);
	
	
	int16_t lastSample = Regenerate(samples[0]);
	size_t lastZero = 0;
	size_t freq = 0;

	
	for(size_t i = 0; i < samplesCount; i++){
		int16_t sample = Regenerate(samples[i]);
		
		if(lastSample == 0 && sample == 0){
			if(freq > 0){
				freqData.push_back(freq);
				freq = 0;
				lastZero = 0;
			}
			lastSample = sample;
			continue;
		}
		
		if(sample == 0){
			if(lastZero > 0){
				if(freq == 0){
					freq += i-lastZero;
				}else{
					freq += i-lastZero;
					freq *= 0.5;
				}	
			}
			lastZero = i;
		}
		lastSample = sample;
		
	}
	
	if(freqData.empty()){
		puts("no detect signal");
		return 0;
	}
	
	size_t lowBitDetect = *std::max_element(freqData.begin(), freqData.end());
	size_t highBitDetect = *std::min_element(freqData.begin(), freqData.end());
	size_t detectLevel = ((lowBitDetect-highBitDetect)*0.5)+highBitDetect;
	
	std::vector<uint8_t> data;
	
	size_t dataSize = freqData.size()/8;
	if(freqData.size() % 8) dataSize++;
	
	
	for(size_t i = 0; i < dataSize; i++){
		uint8_t d = 0;
		for(size_t b = 0; b < 8; b++){
			size_t fData;
			size_t idx = (i*8)+b;
			if(idx < freqData.size()){
				fData = freqData.at(idx);
			}else{
				fData = lowBitDetect;
			}
		
			if(fData < detectLevel){
				d |= (1<<b);
			}
		}
		printf("0x%X | %c\n", d, d);
	}	
	
	return 0;
}
