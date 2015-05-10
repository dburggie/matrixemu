#ifndef _LINKER_H
#define _LINKER_H


namespace matrixemu
{
	template <class T> class Linker
	{
		private:
			T * obj;
			Linker * hp;
			Linker * np;
			Linker * pp;
		public:
			Linker();
			Linker(T * obj);
			Linker(T * obj, Linker * head);
			~Linker();

			Linker * next();
			Linker * prev();

			T * get();
			T * set(T * obj); //returns old pointer

			Linker * append(Linker * chain); //returns head
			Linker * remove(); //returns this
	};
}


#endif
