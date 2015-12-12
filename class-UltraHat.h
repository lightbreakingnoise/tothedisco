class UltraHat
{
	private:
	double phLFO;
	double incLFO;

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
	UltraHat( double LFOfreq )
	{
		incLFO = DP / SR * LFOfreq;
	}

	void Hat( float *out, int note, float vol, int len )
	{
		phLFO = 0.0;
		float freq;
		freq = 27.5*Pitch(note);
		int i;
		int n;
		float phase;
		phase = -1.0;
		float phase2;
		phase2 = -1.0;
		float inc;
		float inc2;
		inc = 2.0 / SR * freq;
		inc2 = inc * 8.0;
		inc *= 7.0;
		float sam;
		float mid;
		mid = 0.8 - (float)((rand()%150) / 100.0);
		float hi;
		hi = 0.0;
		float hi2;
		hi2 = 0.0;
		float hi3;
		hi3 = 0.0;
		float low;
		low = 0.0;
		float low2;
		low2 = 0.0;
		float low3;
		low3 = 0.0;
		float q;
		float superq;
		superq = (freq * 17.0) / HSR;
		float v;
		v = 1.0;
		float vdec;
		vdec = 1.0 / (float)len;
		int x;
		x = 3;
		int mx;
		mx = 30;

		for( n = 0; n < len; n++ )
		{
			q = superq + superq + ( superq * sin(phLFO) );
			phLFO += incLFO;
			if( phLFO >= DP )
				phLFO -= DP;
			
			if( phase < mid )
				sam = -3.0;
			else
				sam = 3.0;
			if( phase2 < 0.0 )
				sam -= 2.0;
			else
				sam += 2.0;
			
			sam += ((float)(rand()%100) / 100.0) - 0.5;
			
			low -= (low - sam) * (q*1.35);
			sam = low;
			hi += (sam - hi) * (q*1.05);
			sam -= hi;
			//low2 -= (low2 - sam) * (q*1.35);
			//sam = low2;
			hi2 += (sam - hi2) * (q*1.05);
			sam -= hi2;
			//low3 -= (low3 - sam) * (q*1.35);
			//sam = low3;
			hi3 += (sam - hi3) * (q*1.05);
			sam -= hi3;
			
			out[n] += v*v * vol * sam;
			v -= vdec;
			
			phase += inc;
			if( phase >= 1.0 )
			{
				x--;
				if( x < 0 )
				{
					x = mx;
					mid = 0.8 - (float)((rand()%150) / 100.0);
					if( mx > 15 )
						mx -= 2;
				}
				phase -= 2.0;
			}
			
			phase2 += inc2;
			if( phase2 >= 1.0 )
				phase2 -= 2.0;
		}
	}
};
