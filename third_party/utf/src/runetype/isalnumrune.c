/* See LICENSE file for copyright and license details. */

int
isalnumrune(Rune r)
{
	return isalpharune(r) || isdigitrune(r);
}
