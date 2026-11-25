/* See LICENSE file for copyright and license details. */

int
ispunctrune(Rune r)
{
	return isgraphrune(r) && !isalnumrune(r);
}
