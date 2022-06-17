#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject
{
	Q_OBJECT

	bool stop;
	unsigned long n;
	double result;

public:
	explicit Worker(QObject * parent = nullptr);

	void set_param(unsigned long n);

	void process();

	double get_result() const;

	~Worker();

	void setStop(bool value);


signals:
	void finished();

	void progress(unsigned i);
};

#endif // WORKER_H
