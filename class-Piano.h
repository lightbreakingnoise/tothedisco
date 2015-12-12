class UltraPiano
{
	private:
	int paus[300];

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
	UltraPiano()
	{
		int i;
		int x;
		for( i = 0; i < 300; i++ )
		{
			if( i%8 == 0 )
				x = 5;
			else
				x = 1;
			paus[i] = (rand()%(70*x)) + (40*x);
		}
	}

	void Piano( float *out, int note, float vol, int len )
	{
		float freq;
		freq = 27.5*Pitch(note);
		int i;
		int n;
		int x;
		float phase;
		phase = -1.0;
		double sph;
		sph = 0.0;
		double sinc;
		sinc = DP / SR * (freq * 0.5);
		float inc;
		inc = 2.0 / SR * freq;
		float sam;
		float sec;
		float thi;
		float flt[20];
		for( i = 0; i < 20; i++ )
			flt[i] = 0.0;
		float q;
		float v;
		v = 1.0;
		float vdec;
		vdec = 1.0 / (float)len;
		float intense;
		intense = 2.7;
		int ff;
		float lowfr;
		lowfr = 4000.0;
		float mid;
		mid = 0.1;
		float g;
		g = 0.05;
		ff = (int)freq;
		int step;
		step = 35;
		while( ff > step )
		{
			g += 0.0015;
			mid *= 0.93;
			ff -= step;
			step += 75;
			intense *= 0.82;
		}
		g *= 9.5;

		for( n = 0; n < len; n++ )
		{
			if( phase < mid )
				sam = -0.4;
			else
				sam = 0.4;
			sam += phase * 0.5;
			
			sam += ((float)(rand()%100) / 400.0) - 0.125;
			sam *= g;
			
			sec = sam;
			thi = sam;
			
			q = (freq * 2.0) / HSR;
			flt[0] -= (flt[0] - sam) * q;
			sam = flt[0];
			flt[1] -= (flt[1] - sam) * q;
			sam = flt[1] * 1.1;
			
			q = 500.0 / HSR;
			flt[2] += (sec - flt[2]) * q;
			sec -= flt[2];
			flt[3] -= (flt[3] - sec) * q;
			sec = flt[3];
			flt[4] += (sec - flt[4]) * q;
			sec -= flt[4];
			flt[5] -= (flt[5] - sec) * q;
			sec = flt[5] * 1.2;
			
			q = 3200.0 / HSR;
			flt[6] += (thi - flt[6]) * q;
			thi -= flt[6];
			flt[7] -= (flt[7] - thi) * q;
			thi = flt[7];
			flt[8] += (thi - flt[8]) * q;
			thi -= flt[8];
			flt[9] -= (flt[9] - thi) * q;
			thi = flt[9] * intense * 0.025;
			
			if( freq < 500.0 )
				sam += sec;
			sam += thi;
			
			if( lowfr > 1500.0 )
				lowfr *= 0.9998;
			
			q = lowfr / HSR;
			flt[10] -= (flt[10] - sam) * q;
			sam = flt[10];
			
			q = freq / HSR;
			q /= 2.0;
			flt[11] += (sam - flt[11]) * q;
			sam -= flt[11];
			
			sam *= v * v * vol;
			out[n] += sam;
			
			q = 1400.0 / HSR;
			flt[12] -= (flt[12] - sam) * q;
			sam = flt[12];

			x = 750;
			sam *= 0.15;
			for( i = 0; i < 300; i++ )
			{
				out[n+x] += sam;
				x += paus[i];
				out[n+x] -= sam;
				i++;
				x += paus[i];
				sam *= 0.98;
			}
			v -= vdec;
			
			phase += inc + (intense * intense * inc * sin(sph) );
			while( phase >= 1.0 )
				phase -= 2.0;
			while( phase <= -1.0 )
				phase += 2.0;
			sph += sinc;
			if( sph >= DP )
				sph -= DP;
		}
	}
};
