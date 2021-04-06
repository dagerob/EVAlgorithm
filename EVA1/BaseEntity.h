class BaseEntity {
public:
	virtual bool mutate(float probability) = 0;
	virtual float getFitness() const = 0;
	virtual BaseEntity* getChildWith(const BaseEntity& other) = 0;
	virtual void print() = 0;
	virtual BaseEntity* getClone() const = 0;
	bool operator<(const BaseEntity& other) {
		return getFitness() < other.getFitness();
	}
	virtual ~BaseEntity() {};
};