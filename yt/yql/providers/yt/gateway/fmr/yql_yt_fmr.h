#pragma once

#include <yt/yql/providers/yt/fmr/coordinator/interface/yql_yt_coordinator.h>
#include <yt/yql/providers/yt/provider/yql_yt_forwarding_gateway.h>

namespace NYql::NFmr {

struct TFmrYtGatewaySettings {
    TIntrusivePtr<IRandomProvider> RandomProvider = CreateDefaultRandomProvider();
    TDuration TimeToSleepBetweenGetOperationRequests = TDuration::Seconds(1);
};

IYtGateway::TPtr CreateYtFmrGateway(
    IYtGateway::TPtr slave,
    IFmrCoordinator::TPtr coordinator = nullptr,
    const TFmrYtGatewaySettings& settings = TFmrYtGatewaySettings{}
);

} // namespace NYql::NFmr
