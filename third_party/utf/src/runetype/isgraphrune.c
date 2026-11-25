/* See LICENSE file for copyright and license details. */

int
isgraphrune(Rune r)
{
	return !isspacerune(r) && isprintrune(r);
}
