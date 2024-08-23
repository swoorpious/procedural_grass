#include "RHIGlobals.h"
#include "RHIShaderParameters.h"
#include "RHIStats.h"



class FMyComputeShader : public FGlobalShader
{
    DECLARE_SHADER_TYPE(FMyComputeShader, Global);

public:
    FMyComputeShader() {}
    FMyComputeShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
        : FGlobalShader(Initializer)
    {
        OutputBuffer.Bind(Initializer.ParameterMap, TEXT("OutputBuffer"));
    }

    void SetParameters(FRHICommandListImmediate& RHICmdList, FUnorderedAccessViewRHIRef UAV)
    {
        SetUAVParameter(RHICmdList, GetComputeShader(), OutputBuffer, UAV);
    }

    void UnbindBuffers(FRHICommandListImmediate& RHICmdList)
    {
        RHICmdList.SetUAVParameter(GetComputeShader(), OutputBuffer.GetBaseIndex(), nullptr);
    }

    // Define shader parameters
    LAYOUT_FIELD(FShaderResourceParameter, OutputBuffer);
};

IMPLEMENT_SHADER_TYPE(, FMyComputeShader, TEXT("/Shaders/MyComputeShader.usf"), TEXT("MainCS"), SF_Compute);
