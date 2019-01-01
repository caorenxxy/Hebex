#ifndef SAMPLING_H
#define SAMPLING_H

#include "../ForwardDecl.h"
#include "Hebex.h"
#include "Utils.h"

namespace Hebex 
{
	struct Distribution1D {
		Distribution1D(const float *f, int n) {
			count = n;
			func = new float[n];
			memcpy(func, f, n * sizeof(float));
			cdf = new float[n + 1];

			cdf[0] = 0.f;
			for (int i = 1; i < count + 1; ++i) 
				cdf[i] = cdf[i - 1] + func[i - 1] / n;

			//transform function intergral into cdf
			funcInt = cdf[count];
			if (funcInt == 0.f) {
				for (int i = 1; i < n + 1; ++i)
					cdf[i] = float(i) / float(n);
			}
			else {
				for (int i = 1; i < n + 1; ++i)
					cdf[i] /= funcInt;
			}
		}

		~Distribution1D() {
			delete[] func;
			delete[] cdf;
		}

		float SampleContinuous(float u, float *pdf, int *off = nullptr) const {
			float *ptr = std::upper_bound(cdf, cdf + count + 1, u);
			int offset = std::max(0, int(ptr - cdf - 1));
			if (off) *off = offset;
			HEBEX_ASSERT(offset < count);
			HEBEX_ASSERT(u >= cdf[offset] && u < cdf[offset + 1]);

			float du = (u - cdf[offset]) / (cdf[offset + 1] - cdf[offset]);
			HEBEX_ASSERT(!IsNaN(du));

			if (pdf) *pdf = func[offset] / funcInt;

			return (offset + du) / count;
		}

		int SampleDiscrete(float u, float *pdf) const {
			float *ptr = std::upper_bound(cdf, cdf + count + 1, u);
			int offset = std::max(0, int(ptr - cdf - 1));
			HEBEX_ASSERT(offset < count);
			HEBEX_ASSERT(u >= cdf[offset] && u < cdf[offset + 1]);
			if (pdf) *pdf = func[offset] / (funcInt * count);

			return offset;
		}

	private:
		friend struct Distribution2D;
		float *func, *cdf;
		float funcInt;
		int count;
	};

	struct Distribution2D {
		// Distribution2D Public Methods
		Distribution2D(const float *func, int nu, int nv) {
			pConditionalV.reserve(nv);
			for (int v = 0; v < nv; ++v) {
				// Compute conditional sampling distribution for $\tilde{v}$
				pConditionalV.push_back(new Distribution1D(&func[v * nu], nu));
			}
			// Compute marginal sampling distribution $p[\tilde{v}]$
			std::vector<float> marginalFunc;
			marginalFunc.reserve(nv);
			for (int v = 0; v < nv; ++v)
				marginalFunc.push_back(pConditionalV[v]->funcInt);
			pMarginal = new Distribution1D(&marginalFunc[0], nv);
		}

		~Distribution2D() {
			delete pMarginal;
			for (uint32_t i = 0; i < pConditionalV.size(); ++i)
				delete pConditionalV[i];
		}

		void SampleContinuous(float u0, float u1, float uv[2],
			float *pdf) const {
			float pdfs[2];
			int v;
			uv[1] = pMarginal->SampleContinuous(u1, &pdfs[1], &v);
			uv[0] = pConditionalV[v]->SampleContinuous(u0, &pdfs[0]);
			*pdf = pdfs[0] * pdfs[1];
		}

		float Pdf(float u, float v) const {
			int iu = Clamp(int(u * pConditionalV[0]->count), 0,
				pConditionalV[0]->count - 1);
			int iv = Clamp(int(v * pMarginal->count), 0,
				pMarginal->count - 1);
			if (pConditionalV[iv]->funcInt * pMarginal->funcInt == 0.f) return 0.f;
			return (pConditionalV[iv]->func[iu] * pMarginal->func[iv]) /
				(pConditionalV[iv]->funcInt * pMarginal->funcInt);
		}
	private:
		// Distribution2D Private Data
		std::vector<Distribution1D *> pConditionalV;
		Distribution1D *pMarginal;
	};



	Vec3f UniformSampleSphere(const Point2f &u);
	float UniformSpherePdf();

	Vec3f UniformSampleCone(const Point2f &u, float thetamax);
	Vec3f UniformSampleCone(const Point2f &u, float thetamax, const Vec3f &x,
		const Vec3f &y, const Vec3f &z);
	float UniformConePdf(float thetamax);
	
}



#endif
