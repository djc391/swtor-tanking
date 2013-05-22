#ifndef SWTOR_TANKING_H
#define SWTOR_TANKING_H

#define RELIC_TYPE_PROC 1
#define RELIC_TYPE_CLICK 2

#define RELIC_STATTYPE_DEF 1
#define RELIC_STATTYPE_SHIELD 2
#define RELIC_STATTYPE_ABSORB 3

extern "C" {
struct ClassData {
	double defenseAdd;
	double defenseBonus;
	double shieldAdd;
	double shieldBonus;
	double absorbAdd;
	double absorbBonus;
	double drAddKE;
	double drAddIE;
	double drBonus;
	double resistPct; 
	unsigned int useKW;
};

typedef struct ClassData classdata_t;

struct StatDistribution {
	unsigned int defRating;
	unsigned int shieldRating;
	unsigned int absorbRating;
};

typedef struct StatDistribution statdist_t;

struct DamageTypes {
	double MRKE;
	double FTKE;
	double FTIE;
};

typedef struct DamageTypes dmgtypes_t;

struct OptimizerResult {
	statdist_t *stats;
	double mitigation;
};

typedef struct OptimizerResult oresult_t;

struct ShieldBounds {
	double low;
	double high;
};

typedef struct ShieldBounds shieldbounds_t;

struct ProcRelic {
	unsigned int stat;
	unsigned int bonus_rating;
	double rate;
	double duration_time;
	double cooldown_time;
	unsigned int can_stack;
};

typedef struct ProcRelic procrelic_t;

struct ClickRelic {
	unsigned int stat1;
	unsigned int stat2;
	unsigned int bonus_rating1;
	unsigned int bonus_rating2;
	double duration_time;
	double cooldown_time;
};

typedef struct ClickRelic clickrelic_t;

union Relic {
	procrelic_t *prelic;
	clickrelic_t *crelic;
};

typedef union Relic relic_t; 

double kineticWardAvgAbsorbBonus(dmgtypes_t *dtypes, double def_miss_pct, double resist_pct, double shield_pct, double time_per_swing);
double relicBonusPct(const unsigned int base_rating, const unsigned int bonus_rating, unsigned int stat);
double procRelicUptime(procrelic_t *relic, dmgtypes_t *dtypes, double def_miss_pct, double resist_pct, double shield_pct, double time_per_swing);
double clickRelicUptime(clickrelic_t *relic);
double defenseChance(const unsigned int rating, const double bonus);
double shieldChance(const unsigned int rating, const double bonus);
double absorbChance(const unsigned int rating, const double bonus);
double dmgReductionKE(const unsigned int armor, const double bonus);
double dmgReductionIE(const double bonus);
double mitigation(dmgtypes_t *dtypes, classdata_t *cdata, statdist_t *stats, unsigned int armor, unsigned int stimDefense, int num_relics, relic_t **relics, unsigned int *relictypes, double time_per_swing);
statdist_t * randomStats(shieldbounds_t * sbounds, const unsigned int budget, rk_state *rand_state_ptr);
oresult_t * optimalStats(dmgtypes_t *dtypes, shieldbounds_t * sbounds, classdata_t *cdata, unsigned int statBudget, unsigned int armor, int num_relics, relic_t **relics, unsigned int *relictypes, unsigned int stimBonus, double time_per_swing, unsigned int numSamples, rk_state *rand_state_ptr);

}

using namespace v8;
using namespace node;

struct OptimizerTask {
	uv_work_t req;
	dmgtypes_t *dtypes;
	shieldbounds_t *sbounds;
	classdata_t *cdata;
	unsigned int statBudget;
	unsigned int armor;
	unsigned int numRelics;
	relic_t **relics;
	unsigned int *relictypes;
	unsigned int stimBonus;
	unsigned int numSamples;
	double time_per_swing;
	rk_state *rand_state;
	oresult_t *output;
	Persistent<Function> callback;
};

typedef struct OptimizerTask opttask_t;

#endif
