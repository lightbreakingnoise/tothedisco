class CodingXDrum
{
	private:
	ITABLE knack;
	ITABLE flow;
	
	float prc( float a, float b, float dist )
	{
		float out;
		float diff;
		
		diff = b - a;
		out = a + (diff*dist);
		
		return out;
	}
	
	public:
	CodingXDrum()
	{
		FillTones( &knack, 0.5, 1.2, 0.8, 1 );
		knack.tones[1] *= 0.2;
		knack.tones[2] *= 0.5;
		knack.tones[7] *= 5.5;
		knack.tones[8] *= 9.5;
		BuildTable( &knack );
		
		FillTones( &flow, 0.5, 1.2, 1.001, 3 );
		BuildTable( &flow );
	}
	
	void BassDrum( float *out, float vol )
	{
		int i;
		double ph;
		ph = 5000.0;
		double fm;
		fm = 0.0;
		double finc;
		finc = DP / SR * 100.0;
		double inc;
		inc = 5000.0 / SR;
		float freq;
		freq = 8000.0;
		float vv;
		vv = 0.0;
		float sil;
		sil = 1.0;
		
		float s;
		float v;
		v = 0.02;
		float q;
		float low1;
		float low2;
		float low3;
		low1 = 0.0;
		low2 = 0.0;
		low3 = 0.0;
		
		float dist;
		dist = 0.0;
				
		for( i = 0; i < 10000; i++ )
		{
			s = ((float)(rand()%500)/500.0) - 0.5;
			s *= v * vol * vv;
			v *= 1.0005;
			
			q = (freq*4.0)  / HSR;
			low1 -= (low1 - s) * q;
			low2 -= (low2 - low1) * q;
			low3 -= (low3 - low2) * q;
			s = low3;
			
			out[i] *= sil;
			out[i] += vv * vol * prc( knack.table[((int)ph)%5000], flow.table[((int)ph)%5000], (1.0 - ((1.0-dist) * 0.35)) );
			out[i] += s;
			
			ph += inc * freq;
			ph += inc * freq * 0.15 * (1.0 - dist) * sin(fm);
			if( freq > 40.0 )
				freq *= 0.9996;
			if( freq > 190.0 )
				freq *= 0.94;
			
			fm += finc;
			
			if( dist < 1.0 )
				dist += 0.002;

			if( i > 8000 )
			{
				vv -= (1.0 / 2000.0);
				sil += ((vol/1.25) / 2000.0);
			}
			if( i < 40 )
			{
				vv += (1.0 / 40.0);
				sil -= ((vol/1.25) / 40.0);
			}
		}
	}
	
	void BassDrumSoft( float *out, float vol )
	{
		int i;
		double ph;
		ph = 5000.0;
		double fm;
		fm = 0.0;
		double finc;
		finc = DP / SR * 100.0;
		double inc;
		inc = 5000.0 / SR;
		float freq;
		freq = 8000.0;
		float vv;
		vv = 0.0;
		float sil;
		sil = 1.0;
		
		float s;
		float v;
		v = 0.02;
		float q;
		float low1;
		float low2;
		float low3;
		low1 = 0.0;
		low2 = 0.0;
		low3 = 0.0;
		
		float dist;
		dist = 0.8;
				
		for( i = 0; i < 5000; i++ )
		{
			s = ((float)(rand()%500)/500.0) - 0.5;
			s *= v * vol * vv;
			v *= 1.0005;
			
			q = (freq*4.0)  / HSR;
			low1 -= (low1 - s) * q;
			low2 -= (low2 - low1) * q;
			low3 -= (low3 - low2) * q;
			s = low3;
			
			//out[i] *= sil;
			out[i] += vv * vol * prc( knack.table[((int)ph)%5000], flow.table[((int)ph)%5000], (1.0 - ((1.0-dist) * 0.35)) );
			out[i] += s;
			
			ph += inc * freq;
			ph += inc * freq * 0.15 * (1.0 - dist) * sin(fm);
			if( freq > 40.0 )
				freq *= 0.9996;
			if( freq > 190.0 )
				freq *= 0.94;
			
			fm += finc;
			
			if( dist < 1.0 )
				dist += 0.002;

			if( i > 3000 )
			{
				vv -= (1.0 / 2000.0);
				sil += ((vol/2.0) / 2000.0);
			}
			if( i < 1000 )
			{
				vv += (1.0 / 1000.0);
				sil -= ((vol/2.0) / 1000.0);
			}
		}
	}
};
