void BuildTable( PTABLE tbl )
{
	int i;
	int n;
	float s;
	double p;
	double inc;
	
	for( n = 0; n < 5000; n++ )
		tbl->table[n] = 0.0;
	
	for( i = 1; i < 100; i++ )
	{
		p = 0.0;
		inc = DP / 5000.0 * (double)i;
		for( n = 0; n < 5000; n++ )
		{
			tbl->table[n] += tbl->tones[i] * sin(p);
			p += inc;
		}
	}
	
	float max;
	max = 0.01;
	for( n = 0; n < 5000; n++ )
	{
		s = tbl->table[n];
		if( s < 0.0 )
			s = -s;
		if( s > max )
			max = s;
	}
	
	float mul;
	mul = 1.0 / max;
	for( n = 0; n < 5000; n++ )
		tbl->table[n] *= mul;
}

void FillTones( PTABLE tbl, float stp, float thi, float mul, int lower )
{
	int i;
	int n;
	float s;
	float v;
	v = 1.0;
	for( i = 1; i < 100; i++ )
	{
		s = v;
		for( n = 1; n <= lower; n++ )
			s /= (float)i;
		
		v *= mul;
		if( i%2 == 0 )
			s *= stp;
		if( i%3 == 0 )
			s *= thi;
		
		tbl->tones[i] = s;
	}
}