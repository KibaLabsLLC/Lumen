/* See LICENSE file for copyright and license details. */

Rune *
runestrrchr(const Rune *s, Rune r)
{
	const Rune *p = NULL;

	for(; *s != 0; s++)
		if(*s == r)
			p = s;

	return (Rune *)p;
}
