class UltraSinus
{
	private:
	int paus[500];

	float Pitch( int p )
	{
		int i;
		float out;
		out = 1.0;
		
		if( p > 0 )
		{
			for( i = 0; i < p; i++ )
				out /= HN;
		}
		
		if( p < 0 )
		{
			for( i = 0; i > p; i-- )
				out *= HN;
		}
		
		return out;
	}

	public:
	UltraSinus()
	{
		int i;
		int x;
		for( i = 0; i < 500; i++ )
		{
			if( i%8 == 0 )
				x = 5;
			else
				x = 1;
			paus[i] = (rand()%(70*x)) + (40*x);
		}
	}

	void Sinus( float *out, int note, float vol, int len )
	{
		float freq;
		freq = 27.5*Pitch(note);
		int i;
		int n;
		int x;
		float phase;
		phase = -1.0;
		float inc;
		inc = 2.0 / SR * freq;
		float sam;
		float flt[20];
		for( i = 0; i < 20; i++ )
			flt[i] = 0.0;
		float q;
		float m;
		m = 2.0;
		float minc;
		minc = 3.0 / (float)len;
		m = 2.0;
		float v;
		v = 0.0;

		for( n = 0; n < len; n++ )
		{
			if( phase < 0.3 )
				sam = -0.7;
			else
				sam = 0.7;
			
			sam += ((float)(rand()%100) / 100.0) - 0.5;
						
			q = (freq * m) / HSR;
			flt[0] -= (flt[0] - sam) * q;
			sam = flt[0];
			flt[1] -= (flt[1] - sam) * q;
			sam = flt[1];
			flt[2] -= (flt[2] - sam) * q;
			sam = flt[2];
			q = freq / HSR;
			flt[3] += (sam - flt[3]) * q;
			sam -= flt[3];

			sam *= v * v * vol;
			out[n] += sam;
			
			q = 1400.0 / HSR;
			flt[12] -= (flt[12] - sam) * q;
			sam = flt[12];

			x = 750;
			sam *= 0.15;
			for( i = 0; i < 500; i++ )
			{
				out[n+x] += sam;
				x += paus[i];
				out[n+x] -= sam;
				i++;
				x += paus[i];
				sam *= 0.985;
			}
			if( n < 200 )
				v += (1.0 / 200.0);
			if( n > len-1500 )
				v -= (1.0 / 1500.0);
			
			m += minc;
			
			phase += inc;
			while( phase >= 1.0 )
				phase -= 2.0;
			while( phase <= -1.0 )
				phase += 2.0;
		}
	}
};
